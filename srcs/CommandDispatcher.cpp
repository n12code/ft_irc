/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:28:29 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 08:14:34 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "CommandDispatcher.hpp"
#include "CommandContext.hpp"
#include "Message.hpp"
#include "PassCommand.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "Client.hpp"
#include <cctype>
#include <algorithm>
#include <iostream>


static Command* createPass(const CommandContext& context) { return new PassCommand(context); }
static Command* createNick(const CommandContext& context) { return new NickCommand(context); }
static Command* createUser(const CommandContext& context) { return new UserCommand(context); }

CommandDispatcher::CommandDispatcher(Server& server, ClientManager &clients) :
    _server(server),
    _clients(clients)
{
    this->_commands["PASS"] = createPass;
    this->_commands["NICK"] = createNick;
    this->_commands["USER"] = createUser;
    //this->_commands["JOIN"] = JoinCommand();
    // this->_commands["PART"] = PartCommand();
    // this->_commands["KICK"] = KickCommand();
    // this->_commands["INVITE"] = InviteCommand();
    // this->_commands["TOPIC"] = TopicCommand();
    // this->_commands["MODE"] = ModeCommand();
    // this->_commands["PRIVMSG"] = PrivMsgCommand();
}

CommandDispatcher::~CommandDispatcher() {}

void    CommandDispatcher::dispatch(int clientFd, Message msg)
{
    std::string command = msg.getCommand();
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    if (command == "QUIT")
        return ;//quit
    
    if (this->_commands.find(command) == this->_commands.end())
    {
        std::cout << "command unknown : "<< command << std::endl;
        return ;//command unknown
    }
    
    Client&         client = this->_clients.getClientWithFd(clientFd);
    CommandContext  context(this->_server, client, this->_clients, msg);//channel
    Command*        cmd = this->_commands[command](context);
    RegRule         rule = cmd->getRule();
    std::string     errorMessage = "";
    
    if (rule == PRE_REG)
    {
        if (client.isRegistered())
            errorMessage = "already registered";
        else if (cmd->isAuthRequired() && !client.isAuth())
            errorMessage = "not registered";
    }
    else if (rule == POST_REG && !client.isRegistered())
        errorMessage = "not registered";
    else if (rule == ANYTIME && !client.isAuth())
        errorMessage = "not registered";

    if (errorMessage.empty() && msg.getParams().size() < cmd->getMinParams())
        errorMessage = "need more params";
        
    if (!errorMessage.empty())
    {
        //send error message
        std::cout << errorMessage << std::endl;
        delete (cmd);
        return ;
    }

    cmd->execute();
    delete (cmd);
}