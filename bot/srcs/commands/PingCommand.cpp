#include "commands/PingCommand.hpp"
#include "Bot.hpp"

std::string cmdPing(Bot& bot, const std::vector<std::string>& args)
{
    (void)bot;
    (void)args;
    return ("pong");
}
