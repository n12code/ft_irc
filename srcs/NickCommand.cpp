/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:34:36 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/12 10:52:01 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include <iostream>

NickCommand::NickCommand(const CommandContext& context):
    Command(context, "NICK", ANYTIME, 1, true) {}

NickCommand::~NickCommand() {}

static bool    isLetter(char c)
{
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
        return (true);
    return (false);
}

static bool    isDigit(char c)
{
    if ('0' <= c && c <= '9')
        return (true);
    return (false);
}

static bool    isSpecial(char c)
{
    if (c == '[' ||
        c == ']' ||
        c == '\\' ||
        c == '`' ||
        c == '_' ||
        c == '^' ||
        c == '{' ||
        c == '|' ||
        c == '}')
        return (true);
    return (false);
}

void    NickCommand::execute()
{
    std::string nick = this->_context.msg.getParams()[0];
    if (!this->isValidNick(nick))
    {
        std::cout << "432 erroneous nick name" << std::endl;
        return ;
    }
    if (this->_context.clients.isNickInUse(nick))
    {
        std::cout << "433 nickname in use " << std::endl;
        return ;
    }
    this->_context.client.setNick(nick);

    std::cout << "NICK SET TO:" << this->_context.client.getNick() << std::endl;
}

bool    NickCommand::isValidNick(const std::string& nick)
{
    if (nick.empty() || nick.size() > 9)
        return (false);
        
    if (!isLetter(nick[0]) &&
        !isSpecial(nick[0]))
        return (false);

    for (size_t i = 1; i < nick.size(); ++i)
    {
        if (!isLetter(nick[0]) &&
            !isDigit(nick[0]) &&
            !isSpecial(nick[0]) &&
            nick[0] != '-')
            return (false);
    }
    return (true);
}