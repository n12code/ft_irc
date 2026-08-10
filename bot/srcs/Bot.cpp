#include "Bot.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

ParsedLine parseLine(const std::string& line)
{
    ParsedLine  result;
    size_t      pos = 0;
    result.hasTrailing = false;

    if (!line.empty() && line[0] == ':')
    {
        size_t space = line.find(' ');
        if (space == std::string::npos)
            return (result);
        result.prefix = line.substr(1, space - 1);
        pos = space + 1;
    }

    size_t space = line.find(' ', pos);
    if (space == std::string::npos)
    {
        result.command = line.substr(pos);
        return (result);
    }
    result.command = line.substr(pos, space - pos);
    pos = space + 1;

    for (;;)
    {
        pos = line.find_first_not_of(' ', pos);
        if (pos == std::string::npos)
            break;
        if (line[pos] == ':')
        {
            result.hasTrailing = true;
            result.trailing = line.substr(pos + 1);
            break;
        }
        size_t nextSpace = line.find(' ', pos);
        if (nextSpace == std::string::npos)
        {
            result.params.push_back(line.substr(pos));
            break;
        }
        result.params.push_back(line.substr(pos, nextSpace - pos));
        pos = nextSpace;
    }
    return (result);
}

std::string extractNick(const std::string& prefix)
{
    size_t excl = prefix.find('!');
    if (excl == std::string::npos)
        return (prefix);
    return (prefix.substr(0, excl));
}

std::vector<std::string> extractArgs(const std::string& text, size_t afterCmdPos)
{
    std::vector<std::string> args;
    size_t pos = afterCmdPos;

    for (;;)
    {
        pos = text.find_first_not_of(' ', pos);
        if (pos == std::string::npos)
            break;
        size_t nextSpace = text.find(' ', pos);
        if (nextSpace == std::string::npos)
        {
            args.push_back(text.substr(pos));
            break;
        }
        args.push_back(text.substr(pos, nextSpace - pos));
        pos = nextSpace;
    }
    return (args);
}

static std::string cmdPing(Bot& bot, const std::vector<std::string>& args)
{
    (void)bot;
    (void)args;
    return ("pong");
}

void Bot::handleIncoming(const char* data, ssize_t len)
{
    this->_readBuffer.append(data, len);

    size_t pos;
    while ((pos = this->_readBuffer.find('\n')) != std::string::npos)
    {
        std::string line = this->_readBuffer.substr(0, pos);
        this->_readBuffer.erase(0, pos + 1);
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);
        if (line.empty())
            continue;

        std::cout << "[SERVER] " << line << std::endl;   // garde ça pour debug, retire plus tard

        ParsedLine parsed = parseLine(line);
        this->dispatchCommand(parsed);
    }
}

Bot::~Bot()
{}

Bot::Bot(): _user("default"), _nick("default"), _fd(1)
{
    this->initCommands();
}

Bot::Bot(std::string &user, std::string &nick, int fd):
_user(user), _nick(nick), _fd(fd)
{
    this->initCommands();
}

static std::string cmdSendFile(Bot& bot, const std::vector<std::string>& args)
{
    if (args.size() < 2)
        return ("Usage: !sendfile <bot> <file>");
    bot.startFileTransfer(args[0], args[1]);
    return ("Sending " + args[1] + " to " + args[0] + "...");
}

void Bot::handleFileEnd(const std::string& sender, const std::string& text)
{
    (void)sender;
    std::istringstream iss(text);
    std::string cmd;
    int transferId;
    iss >> cmd >> transferId;

    std::map<int, FileTransfer>::iterator it = this->_pendingTransfers.find(transferId);
    if (it == this->_pendingTransfers.end())
        return;
    FileTransfer& t = it->second;

    std::string rawData = base64Decode(t.accumulatedBase64);
    if (computeMD5(rawData) != t.expectedMd5)
    {
        std::cerr << "Corrupted file: " << t.filename << std::endl;
        this->_pendingTransfers.erase(it);
        return;
    }

    std::ofstream out(t.filename.c_str(), std::ios::binary);
    out.write(rawData.data(), rawData.size());
    out.close();

    std::cout << "File " << t.filename << " received successfully." << std::endl;
    this->_pendingTransfers.erase(it);
}

void Bot::handleFileData(const std::string& sender, const std::string& text)
{
    (void)sender;
    std::istringstream iss(text);
    std::string cmd;
    int transferId;
    iss >> cmd >> transferId;

    size_t prefixLen = cmd.size() + 1 + toStringLen(transferId) + 1;   // ou trouve la position autrement
    std::string chunk = text.substr(text.find(' ', text.find(' ') + 1) + 1);

    this->_pendingTransfers[transferId].accumulatedBase64 += chunk;
}

struct FileTransfer
{
    std::string sender;
    std::string filename;
    size_t      expectedSize;
    std::string expectedMd5;
    std::string accumulatedBase64;
};

std::map<int, FileTransfer> _pendingTransfers;   // clé = transferId, PAS le nick (on l'avait vu ensemble)

void Bot::handleFileSend(const std::string& sender, const std::string& text)
{
    std::istringstream iss(text);
    std::string cmd;
    int transferId;
    std::string filename;
    size_t size;
    std::string md5;
    iss >> cmd >> transferId >> filename >> size >> md5;

    FileTransfer t;
    t.sender = sender;
    t.filename = filename;
    t.expectedSize = size;
    t.expectedMd5 = md5;
    this->_pendingTransfers[transferId] = t;

    std::cout << sender << " wants to send " << filename << " (" << size << " bytes)" << std::endl;
}

void Bot::startFileTransfer(const std::string& targetNick, const std::string& filepath)
{
    std::ifstream file(filepath.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filepath << std::endl;
        return;
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string rawData = ss.str();

    std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
    std::string md5 = computeMD5(rawData);
    std::string encoded = base64Encode(rawData);

    int transferId = this->_nextTransferId++;   // simple compteur, membre de Bot

    std::ostringstream offer;
    offer << "FILESEND " << transferId << " " << filename << " " << rawData.size() << " " << md5;
    this->sendRaw("PRIVMSG " + targetNick + " :" + offer.str() + "\r\n");

    const size_t CHUNK_SIZE = 400;
    for (size_t i = 0; i < encoded.size(); i += CHUNK_SIZE)
    {
        std::ostringstream chunkMsg;
        chunkMsg << "FILEDATA " << transferId << " " << encoded.substr(i, CHUNK_SIZE);
        this->sendRaw("PRIVMSG " + targetNick + " :" + chunkMsg.str() + "\r\n");
    }

    std::ostringstream endMsg;
    endMsg << "FILEEND " << transferId;
    this->sendRaw("PRIVMSG " + targetNick + " :" + endMsg.str() + "\r\n");
}

void Bot::connexion(std::string &password)
{
    std::string realname = this->_nick + "_bot";
    std::string connexion_pass = "PASS " + password + "\r\n";
    std::string connexion_user = "USER " + this->_user + " 0 * :" + realname + "\r\n";
    std::string connexion_nick = "NICK " + this->_nick + "\r\n";
    std::string test = "JOIN #test\r\n";
    send(this->_fd, connexion_pass.c_str(), connexion_pass.size(), 0);
    send(this->_fd, connexion_user.c_str(), connexion_user.size(), 0);
    send(this->_fd, connexion_nick.c_str(), connexion_nick.size(), 0);
    send(this->_fd, test.c_str(), test.size(), 0);
}

void Bot::dispatchCommand(const ParsedLine& parsed)
{
    if (parsed.command != "PRIVMSG" || parsed.params.empty() || !parsed.hasTrailing)
        return;

    const std::string& target = parsed.params[0];
    const std::string& text   = parsed.trailing;
    std::string sender = extractNick(parsed.prefix);

    if (text.compare(0, 8, "FILESEND") == 0)
    {
        this->handleFileSend(sender, text);
        return;
    }
    if (text.compare(0, 8, "FILEDATA") == 0)
    {
        this->handleFileData(sender, text);
        return;
    }
    if (text.compare(0, 7, "FILEEND") == 0)
    {
        this->handleFileEnd(sender, text);
        return;
    }

    if (text.empty() || text[0] != '!')
        return;

    size_t space = text.find(' ');
    std::string cmdName = text.substr(1, space - 1);
    std::vector<std::string> args = extractArgs(text, space);

    std::string replyTo;
    if (target[0] == '#')
        replyTo = target;
    else
        replyTo = extractNick(parsed.prefix);
    std::map<std::string, BotCommandHandler>::iterator it = this->_commands.find(cmdName);
    if (it != this->_commands.end())
    {
        std::string reply = it->second(*this, args);
        this->sendRaw("PRIVMSG " + replyTo + " :" + reply + "\r\n");
    }
}

void Bot::sendRaw(const std::string& line)
{
    send(this->_fd, line.c_str(), line.size(), 0);
}

void Bot::initCommands()
{
    this->_commands["ping"] = &cmdPing;
}

int Bot::getFd() const
{
    return (this->_fd);
}

const std::string& Bot::getNick() const
{
    return (this->_nick);
}
