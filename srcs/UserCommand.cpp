/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:37:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 08:13:57 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"
#include "Message.hpp"
#include "Client.hpp"

#include <iostream>

UserCommand::UserCommand(const CommandContext &context):
    Command(context, "USER", PRE_REG, 4, true){}

UserCommand::~UserCommand() {}

void    UserCommand::execute()
{
    std::string user = this->_context.msg.getParams()[0];

    if (user.empty())
        std::cout << "461 need more params" << std::endl;
    this->FormatUser(user);
    
    this->_context.client.setUser(user);
    if (!this->_context.client.getNick().empty())
        this->_context.client.setRegistered(true);

    std::cout << "user :" << this->_context.client.getUser() << std::endl;
    std::cout << this->_context.client.isAuth() << std::endl;
    std::cout << this->_context.client.isRegistered() << std::endl;
}

void UserCommand::FormatUser(std::string &user)
{
    for (size_t i = 0; i < user.size(); ++i)
    {
        if (user[i] == ' ' || user[i] == '@')
            user[i] = '_';
    }
}
