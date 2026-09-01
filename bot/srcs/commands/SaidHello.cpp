#include "commands/SaidHelloCommand.hpp"
#include "Bot.hpp"
#include <iostream>

std::string cmdSaidHello(Bot& bot, const std::vector<std::string>& args)
{//!SAIDHELLO <0(talk) 1(set)> <citation>
    if (args.size()!= 2)
        return ("Format: <option> <citation>"); 
    if (args[0].compare("0") == 0)
        return (args[1]);
    else if(args[0].compare("1") == 0)
    {
        bot.saidHello = args[1];
        return ("Initialise of SaidHello to:" + args[1]);
    }
    return ("Unknow the arg: " + args[0]);
}
