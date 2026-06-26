/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:34:36 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/26 07:54:39 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include "Status.hpp"
#include "Replies.hpp"
#include <iostream>
#include <ctime>

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
    Client& client = this->_context.client;
    std::string currentNick = client.getNick();
    
    if (currentNick.empty())
            currentNick = "*";
    if (!this->isValidNick(nick))
    {
        client.sendMessage(Replies::create(ERR_ERRONEUSNICKNAME, currentNick, nick));
        return ;
    }
    if (this->_context.clients.hasClient(nick))
    {
        client.sendMessage(Replies::create(ERR_NICKNAMEINUSE, currentNick, nick));
        return ;
    }
    client.setNick(nick);

    if (!client.getUser().empty())
    {
        std::string prefix = client.getNick() + "!" + client.getUser() + "@" + client.getHost();
        client.setPrefix(prefix);
        if (!client.isRegistered())
        {
            std::time_t   time = std::time(NULL);
            char*         timeStr = std::ctime(&time);
            client.setRegistered(true);
            client.sendMessage(Replies::create(RPL_WELCOME, client.getNick(), client.getPrefix()));
            client.sendMessage(Replies::create(RPL_YOURHOST, client.getNick(), "1.0"));
            client.sendMessage(Replies::create(RPL_CREATED, client.getNick(), std::string(timeStr)));
            client.sendMessage(Replies::create(RPL_MYINFO, client.getNick(), "1.0", "", "itokl"));
        }
    }
    std::cout << "NICK SET TO:" << client.getNick() << std::endl;
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