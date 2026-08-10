#ifndef BOT_HPP
# define BOT_HPP

# include <string>
# include <vector>
# include <map>
# include <sys/types.h>

struct ParsedLine
{
    std::string                 prefix;
    std::string                 command;
    std::vector<std::string>    params;
    bool                        hasTrailing;
    std::string                 trailing;
};

class Bot;

typedef std::string (*BotCommandHandler)(Bot& bot, const std::vector<std::string>& args);

class Bot
{
private:
    std::string                                _user;
    std::string                                _nick;
    int                                         _fd;
    std::string                                 _readBuffer;
    std::map<std::string, BotCommandHandler>    _commands;

    void    initCommands();

public:
    Bot();
    Bot(std::string &user, std::string &nick, int fd);
    ~Bot();

    void    connexion(std::string &password);
    void    startFileTransfer(const std::string& targetNick, const std::string& filepath);
    void    handleIncoming(const char* data, ssize_t len);
    void    dispatchCommand(const ParsedLine& parsed);
    void    sendRaw(const std::string& line);

    int                 getFd() const;
    const std::string&  getNick() const;
};

ParsedLine                  parseLine(const std::string& line);
std::string                 extractNick(const std::string& prefix);
std::vector<std::string>    extractArgs(const std::string& text, size_t afterCmdPos);

#endif