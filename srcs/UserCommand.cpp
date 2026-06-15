/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:37:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/15 10:59:50 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Status.hpp"
#include <iostream>

UserCommand::UserCommand(const CommandContext& context):
    Command(context, "USER", PRE_REG, 4, true){}

UserCommand::~UserCommand() {}

void    UserCommand::execute()
{
    std::string user = this->_context.msg.getParams()[0];
    std::string realname = this->_context.msg.getParams()[3];

    if (user.empty() || realname.empty())
        std::cout << "461 need more params" << std::endl;
    this->FormatUser(user);
    
    Client& client = this->_context.client;
    client.setUser(user);
    client.setRealName(realname);
    if (!client.getNick().empty())
    {
        client.setRegistered(true);
        std::string prefix = client.getNick() + "!" + client.getUser() + "@" + client.getHost();
        client.setPrefix(prefix);
        this->_context.client.sendMessage(Replies::create(RPL_WELCOME, client.getNick(), client.getPrefix()));
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
