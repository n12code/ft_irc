/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:37:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/25 07:58:54 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Status.hpp"
#include <iostream>
#include <ctime>

UserCommand::UserCommand(const CommandContext& context):
    Command(context, "USER", PRE_REG, 4, true){}

UserCommand::~UserCommand() {}

void    UserCommand::execute()
{
    std::string user = this->_context.msg.getParams()[0];
    std::string realname = this->_context.msg.getParams()[3];

    this->FormatUser(user);
    
    Client& client = this->_context.client;
    client.setUser(user);
    client.setRealName(realname);
    if (!client.getNick().empty())
    {
        std::string prefix = client.getNick() + "!" + client.getUser() + "@" + client.getHost();
        client.setPrefix(prefix);
        client.setRegistered(true);
        
        std::time_t   time = std::time(NULL);
        char*         timeStr = std::ctime(&time);
        
        client.sendMessage(Replies::create(RPL_WELCOME, client.getNick(), client.getPrefix()));
        client.sendMessage(Replies::create(RPL_YOURHOST, client.getNick(), "1.0"));
        client.sendMessage(Replies::create(RPL_CREATED, client.getNick(), std::string(timeStr)));
        client.sendMessage(Replies::create(RPL_MYINFO, client.getNick(), "1.0", "0", "itokl"));
    }

    std::cout << "USER SET TO :" << client.getUser() << std::endl;
    if (client.isAuth())
        std::cout << client.getUser() << " is authenticated" << std::endl;
    if (client.isRegistered())
        std::cout << client.getUser() << " is registered" << std::endl;
    std::cout <<std::endl;
}

void UserCommand::FormatUser(std::string &user)
{
    for (size_t i = 0; i < user.size(); ++i)
    {
        if (user[i] == ' ' || user[i] == '@')
            user[i] = '_';
    }
}


// << PASS irc

// << NICK Alice

// << USER Alice 0 * :realname

// >> :localhost 462 :Unauthorized command (already registered)

// >> :localhost 451 :You have not registered

// >> :localhost 462 :Unauthorized command (already registered)


// this happens when i try to connect, even tho its the first time i ever connect with this user. it didnt do that before we changed the sending system