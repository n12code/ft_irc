#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <vector>
#include <map>
#include <sys/types.h>
#include "LineParser.hpp"
#include "FileTransfert.hpp"
#include "Crc32.hpp"

class Bot;

typedef std::string (*BotCommandHandler)(Bot& bot, const std::vector<std::string>& args);

class Bot
{
private:
    std::string                                 _user;
    std::string                                 _nick;
    int                                         _fd;
    std::string                                 _readBuffer;
    std::map<std::string, BotCommandHandler>    _commands;
    std::map<int, FileTransfer>                 _pendingTransfers;
    int                                         _nextTransferId;

    void    initCommands();

public:
    std::string                                 saidHello;
    Bot();
    Bot(std::string &user, std::string &nick, int fd);
    ~Bot();

    void    connection(std::string &password);
    void    handleIncoming(const char* data, ssize_t len);
    void    dispatchCommand(const ParsedLine& parsed);
    void    sendRaw(const std::string& line);

    void    startFileTransfer(const std::string& targetNick, const std::string& filepath);
    void    handleFileSend(const std::string& sender, const std::string& text);
    void    handleFileData(const std::string& sender, const std::string& text);
    void    handleFileEnd(const std::string& sender, const std::string& text);

    int                 getFd() const;
    const std::string&  getNick() const;
};

#endif