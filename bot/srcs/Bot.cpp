#include "Bot.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Base64.hpp"

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

        std::cout << "[SERVER] " << line << std::endl;   // debug

        ParsedLine parsed = parseLine(line);
        this->dispatchCommand(parsed);
    }
}

Bot::~Bot()
{}

Bot::Bot(): _user("default"), _nick("default"), _fd(1), _nextTransferId(0)
{
    this->initCommands();
}

Bot::Bot(std::string &user, std::string &nick, int fd):
_user(user), _nick(nick), _fd(fd), _nextTransferId(0)
{
    this->initCommands();
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
    if (computeCrc32(rawData) != t.expectedcrc32)
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

    std::string chunk = text.substr(text.find(' ', text.find(' ') + 1) + 1);

    this->_pendingTransfers[transferId].accumulatedBase64 += chunk;
}

void Bot::handleFileSend(const std::string& sender, const std::string& text)
{
    std::istringstream iss(text);
    std::string cmd;
    int transferId;
    std::string filename;
    size_t size;
    std::string crc32;
    iss >> cmd >> transferId >> filename >> size >> crc32;

    FileTransfer t;
    t.sender = sender;
    t.filename = filename;
    t.expectedSize = size;
    t.expectedcrc32 = crc32;
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
    std::string crc32 = computeCrc32(rawData);
    std::string encoded = base64Encode(rawData);

    int transferId = this->_nextTransferId++;

    std::ostringstream offer;
    offer << "FILESEND " << transferId << " " << filename << " " << rawData.size() << " " << crc32;
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
#include <iostream>
void Bot::dispatchCommand(const ParsedLine& parsed)
{
    if (!this->saidHello.empty() && parsed.command == "JOIN")//setup to welcome a new user
    {   
        std::cout << "A new user" << std::endl;
        this->sendRaw("PRIVMSG #test :" + this->saidHello + "\r\n");
    }
    else if (parsed.command != "PRIVMSG" || parsed.params.empty() || !parsed.hasTrailing)//others commands
        return;
    else
    {
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
}

void Bot::sendRaw(const std::string& line)
{
    send(this->_fd, line.c_str(), line.size(), 0);
}

int Bot::getFd() const
{
    return (this->_fd);
}

const std::string& Bot::getNick() const
{
    return (this->_nick);
}
