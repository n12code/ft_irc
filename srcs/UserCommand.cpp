/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:37:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/26 08:18:47 by nbodin           ###   ########lyon.fr   */
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
    if (!client.getUser().empty())
    {
        client.sendMessage(Replies::create(ERR_ALREADYREGISTERED, client.getNick(), this->_name));
        return ;
    }
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
}

void UserCommand::FormatUser(std::string &user)
{
    for (size_t i = 0; i < user.size(); ++i)
    {
        if (user[i] == ' ' || user[i] == '@')
            user[i] = '_';
    }
}