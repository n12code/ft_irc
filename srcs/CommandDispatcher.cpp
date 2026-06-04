/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:28:29 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 09:26:28 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "CommandDispatcher.hpp"
#include "Message.hpp"
#include "JoinCommand.hpp"
#include <cctype>
#include <algorithm>


CommandDispatcher::CommandDispatcher() 
{
    // this->_commands["PASS"] = PassCommand();
    // this->_commands["NICK"] = NickCommand();
    // this->_commands["USER"] = UserCommand();
    // this->_commands["QUIT"] = QuitCommand();
    this->_commands["JOIN"] = JoinCommand();
    // this->_commands["PART"] = PartCommand();
    // this->_commands["KICK"] = KickCommand();
    // this->_commands["INVITE"] = InviteCommand();
    // this->_commands["TOPIC"] = TopicCommand();
    // this->_commands["MODE"] = ModeCommand();
    // this->_commands["PRIVMSG"] = PrivMsgCommand();
    //PING ?
}

CommandDispatcher::~CommandDispatcher()
{
}

void    CommandDispatcher::dispatch(Message& msg)
{
    std::string command = msg.getCommand();
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    if (this->_commands.find(command) != this->_commands.end())
        //this->_commands[command].execute(msg);
}