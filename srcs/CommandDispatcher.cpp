/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:28:29 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 00:54:53 by ubuntu           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "CommandDispatcher.hpp"
#include "CommandContext.hpp"
#include "Message.hpp"
#include "PassCommand.hpp"
#include "Client.hpp"
#include <cctype>
#include <algorithm>
#include <iostream>


static Command* createPass(const CommandContext& context) { return new PassCommand(context); }

CommandDispatcher::CommandDispatcher(Server& server, ClientManager &clients) :
    _server(server),
    _clients(clients)
{
    this->_commands["PASS"] = createPass;
    // this->_commands["NICK"] = NickCommand();
    // this->_commands["USER"] = UserCommand();
    // this->_commands["QUIT"] = QuitCommand();
    //this->_commands["JOIN"] = JoinCommand();
    // this->_commands["PART"] = PartCommand();
    // this->_commands["KICK"] = KickCommand();
    // this->_commands["INVITE"] = InviteCommand();
    // this->_commands["TOPIC"] = TopicCommand();
    // this->_commands["MODE"] = ModeCommand();
    // this->_commands["PRIVMSG"] = PrivMsgCommand();
    //PING ?
}

CommandDispatcher::~CommandDispatcher() {}

void    CommandDispatcher::dispatch(int clientFd, Message msg)
{
    std::string command = msg.getCommand();
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    if (this->_commands.find(command) == this->_commands.end())
    {
        std::cout << "command unknown : "<< command << std::endl;
        return ;//command unknown
    }
    
    Client& client = this->_clients.getClientWithFd(clientFd);
    CommandContext  context(this->_server, client, this->_clients, msg);//channel
    Command*        cmd = this->_commands[command](context);
    
    if (cmd->isAuthRequired() && !client.isRegistered())// is it the correct check ?
        return ;//client not registered

    cmd->execute();
}