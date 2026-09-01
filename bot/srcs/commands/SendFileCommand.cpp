#include "commands/SendFileCommand.hpp"
#include "Bot.hpp"

std::string cmdSendFile(Bot& bot, const std::vector<std::string>& args)
{
    if (args.size() < 2)
        return ("Format: <bot> <path_file>");
    bot.startFileTransfer(args[0], args[1]);
    return ("Sending " + args[1] + " to " + args[0]);
}
