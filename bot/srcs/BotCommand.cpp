#include "Bot.hpp"
#include "commands/PingCommand.hpp"
#include "commands/SendFileCommand.hpp"
#include "commands/SaidHelloCommand.hpp"


void Bot::initCommands()
{
    this->_commands["ping"] = &cmdPing;
    this->_commands["sendfile"] = &cmdSendFile;
    this->_commands["saidhello"] = &cmdSaidHello;
}