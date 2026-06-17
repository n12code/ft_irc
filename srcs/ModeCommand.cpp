/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:33:22 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/17 10:54:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCommand.hpp"
#include "Message.hpp"
#include "ChannelManager.hpp"
#include "Channel.hpp"
#include "ClientManager.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Status.hpp"
#include <sstream>
#include <cstdlib>

ModeCommand::ModeCommand(const CommandContext &context):
    Command(context, "MODE", POST_REG, 1, true) {}

ModeCommand::~ModeCommand() {}

//ERR_CHANOPRIVSNEEDED

// ERR_NEEDMOREPARAMS              ERR_KEYSET                 
// ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE

// RPL_CHANNELMODEIS

// RPL_BANLIST                     RPL_ENDOFBANLIST
// RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
// RPL_INVITELIST                  RPL_ENDOFINVITELIST

// RPL_UNIQOPIS

void    ModeCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    Client&                     client = this->_context.client;
    bool                        adding = false;
    size_t                      totalArgModes = 0;
    size_t                      paramIdx = 1;

    if (!this->_context.channels.hasChannel(params[0]))
    {
        client.sendMessage(Replies::create(ERR_NOSUCHCHANNEL, client.getNick(), params[0]));
        return ;   
    }

    Channel&    chan = this->_context.channels.getChannelByName(params[0]);
    params.erase(params.begin());
    if (params.size() == 0)
    {   
        sendChannelModes(client, chan);
        return ;
    }
    
    if (!chan.isChanop(this->_context.client.getFd()))
    {
        client.sendMessage(Replies::create(ERR_CHANOPRIVSNEEDED, client.getNick(), chan.getName()));
        return ;
    }
    
    for (size_t i = 0; i < params.size(); ++i)
    {
        //skip
        if (params[i][0] != '+' && params[i][0] != '-')
        {
            if (i == 0)
            {
                client.sendMessage(Replies::create(ERR_UNKNOWNMODE, client.getNick(), std::string(1, params[i][0]), chan.getName()));
                return ;
            }
            continue ;
        }
        //mode block
        if (paramIdx <= i)
            paramIdx = i + 1;
        for (size_t j = 0; j < params[i].size(); ++j)
        {
            char    c = params[i][j];
            if (c == '+')
                adding = true;
            else if (c == '-')
                adding = false;
            else if (c == 'k' || c == 'o' || (c == 'l' && adding))
            {
                if (handleParamModes(totalArgModes, paramIdx    , adding, c, params, client, chan) == -1)
                    continue ;
            }
            else if (c == 'i' || c == 't' || (c == 'l' && !adding))
            {
                if (adding)
                    chan.addMode(c);
                else
                    chan.removeMode(c);
            }
            else
            {
                client.sendMessage(Replies::create(ERR_UNKNOWNMODE, client.getNick(), std::string(1, c), chan.getName()));
                continue ;
            }
        }   
    }
}

void    ModeCommand::sendChannelModes(const Client& client, const Channel& chan)
{
    std::string modes = "+";
    std::string modeParams = "";

    if (chan.hasMode('i'))
        modes += "i";
    if (chan.hasMode('t'))
        modes += "t";
    if (chan.hasMode('k'))
    {
        modes += "k";
        modeParams += " " + chan.getPassword();
    }
    if (chan.hasMode('l'))
    {
        modes += "l";
        std::stringstream ss;
        ss << chan.getMaxCap();
        modeParams += " " + ss.str();
    }
    client.sendMessage(Replies::create(RPL_CHANNELMODEIS, client.getNick(), chan.getName(), modes, modeParams));
}


int     ModeCommand::getClientFd(const std::string& arg, const Client& client, const Channel& chan)
{
    if (!this->_context.clients.hasClient(arg))
    {
        client.sendMessage(Replies::create(ERR_NOSUCHNICK, client.getNick(), arg));
        return (-1);
    }
    int clientFd = this->_context.clients.getClientWithNick(arg).getFd();
    if (!chan.isUser(clientFd))
    {
        client.sendMessage(Replies::create(ERR_USERNOTINCHANNEL, client.getNick(), arg, chan.getName()));
        return (-1);
    }
    return (clientFd);
}

int     ModeCommand::handleParamModes(size_t& totalArgModes, size_t& paramIdx, const bool adding, const char c, const std::vector<std::string>& params, const Client& client, Channel& chan)
{
    if (totalArgModes >= 3)
        return (-1);
    totalArgModes++;
    
    while (paramIdx < params.size() && (params[paramIdx][0] == '+' || params[paramIdx][0] == '-'))
        paramIdx++;
        
    if (paramIdx >= params.size())
    {
        client.sendMessage(Replies::create(ERR_NEEDMOREPARAMS, client.getNick(), this->getName()));
        return (-1);
    }
    std::string arg = params[paramIdx++];
    
    if (adding)
    {
        if (c == 'k')
        {
            if (chan.hasMode('k'))
            {
                client.sendMessage(Replies::create(ERR_KEYSET, client.getNick(), chan.getName()));
                return (-1);
            }
            chan.setPassword(arg);
            chan.addMode('k');
        }
        else if (c == 'o')
        {
            int clientFd = getClientFd(arg, client, chan);
            if (clientFd == -1)
                return (-1);
            chan.addChanop(clientFd);
        }
        else
        {
            size_t  limit = atol(arg.c_str());
            if (limit <= 0)
                return (-1);
            chan.setMaxCap(limit);
            chan.addMode('l');
        }
    }
    else
    {
        if (c == 'k')
        {
            if (arg != chan.getPassword())
                return (-1);
            chan.setPassword("");
            chan.removeMode('k');
        }
        else if (c == 'o')
        {
            int clientFd = getClientFd(arg, client, chan);
            if (clientFd == -1)
                return (-1);
            chan.removeChanop(clientFd);
        }
    }
    return (0);
}


