/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:33:22 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 07:30:33 by nbodin           ###   ########lyon.fr   */
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
#include "ModeTracker.hpp"
#include <sstream>
#include <cstdlib>

ModeCommand::ModeCommand(const CommandContext &context):
    Command(context, "MODE", POST_REG, 1, true) {}

ModeCommand::~ModeCommand() {}

void    ModeCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    Client&                     client = this->_context.client;
    ModeTracker                 tracker;

    if (!this->_context.channels.hasChannel(params[0]))
    {
        client.sendMessage(Replies::create(ERR_NOSUCHCHANNEL, client.getNick(), params[0]));
        return ;   
    }

    Channel&    chan = this->_context.channels.getChannelByName(params[0]);
    params.erase(params.begin());
    if (params.size() == 0)
    {   
        this->sendChannelModes(client, chan);
        return ;
    }
    
    if (!chan.isChanop(this->_context.client.getFd()))
    {
        client.sendMessage(Replies::create(ERR_CHANOPRIVSNEEDED, client.getNick(), chan.getName()));
        return ;
    }
    
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (params[i][0] != '+' && params[i][0] != '-')
        {
            if (i == 0)
            {
                client.sendMessage(Replies::create(ERR_UNKNOWNMODE, client.getNick(), std::string(1, params[i][0]), chan.getName()));
                return ;
            }
            continue ;
        }
        if (tracker.argIndex <= i)
            tracker.argIndex = i + 1;
        for (size_t j = 0; j < params[i].size(); ++j)
        {
            char    c = params[i][j];
            if (c == '+')
                tracker.adding = true;
            else if (c == '-')
                tracker.adding = false;
            else if (c == 'k' || c == 'o' || (c == 'l' && tracker.adding))
            {
                if (this->handleParamModes(c, params, client, chan, tracker) == -1)
                    continue ;
            }
            else if (c == 'i' || c == 't' || (c == 'l' && !tracker.adding))
            {
                if (tracker.adding)
                {
                    if (chan.hasMode(c))
                        continue ;
                    chan.addMode(c);
                    this->appendModeAndArg(tracker, '+', c);
                }
                else
                {
                    if (!chan.hasMode(c))
                        continue ;
                    chan.removeMode(c);
                    this->appendModeAndArg(tracker, '-', c);
                }
            }
            else
            {
                client.sendMessage(Replies::create(ERR_UNKNOWNMODE, client.getNick(), std::string(1, c), chan.getName()));
                continue ;
            }
        }   
    }
    if (!tracker.addedModes.empty() || !tracker.removedModes.empty())
        this->sendModeMessage(tracker, client, chan);
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

int     ModeCommand::handleParamModes(const char c, const std::vector<std::string>& params, const Client& client, Channel& chan, ModeTracker& tracker)
{
    if (tracker.totalArgModes >= 3)
        return (-1);
    
    while (tracker.argIndex < params.size() && (params[tracker.argIndex][0] == '+' || params[tracker.argIndex][0] == '-'))
        tracker.argIndex++;
        
    if (tracker.argIndex >= params.size())
    {
        client.sendMessage(Replies::create(ERR_NEEDMOREPARAMS, client.getNick(), this->getName()));
        return (-1);
    }
    std::string arg = params[tracker.argIndex++];
    
    if (tracker.adding)
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
            if (clientFd == -1 || chan.isChanop(clientFd))
                return (-1);
            chan.addChanop(clientFd);
        }
        else
        {
            if (arg.size() >= 6)
                return (-1);
            for (size_t i = 0; i < arg.size(); ++i)
            {
                if (!isdigit(arg[i]))
                    return (-1);
            }
            size_t  limit = atol(arg.c_str());
            if (limit <= 0 || (chan.hasMode('l') && chan.getMaxCap() == limit))
                return (-1);
            chan.setMaxCap(limit);
            chan.addMode('l');
        }
        this->appendModeAndArg(tracker, '+', c, arg);
    }
    else
    {
        if (c == 'k')
        {
            if (!chan.hasMode('k') || arg != chan.getPassword())
                return (-1);
            chan.setPassword("");
            chan.removeMode('k');
        }
        else if (c == 'o')
        {
            int clientFd = getClientFd(arg, client, chan);
            if (clientFd == -1 || !chan.isChanop(clientFd))
                return (-1);
            chan.removeChanop(clientFd);
        }
        this->appendModeAndArg(tracker, '-', c, arg);
    }
    tracker.totalArgModes++;
    return (0);
}

void    ModeCommand::appendModeAndArg(ModeTracker& tracker, char sign, char mode, const std::string& arg)
{
    std::string& modes = (sign == '+') ? tracker.addedModes : tracker.removedModes;
    std::string& args = (sign == '+') ? tracker.addedArgs : tracker.removedArgs;
    
    modes += mode;
    if (!arg.empty())
    {
        if (!args.empty())
            args += " ";
        args += arg;
    }
}

void    ModeCommand::sendModeMessage(const ModeTracker& tracker, const Client& client, const Channel& chan)
{
    std::string finalModes;
    if (!tracker.addedModes.empty())
        finalModes += "+" + tracker.addedModes;
    if (!tracker.removedModes.empty())
        finalModes += "-" + tracker.removedModes;

    std::string finalArgs;
    if (!tracker.addedArgs.empty())
        finalArgs += tracker.addedArgs;;
    if (!tracker.removedArgs.empty())
    {
        if (!finalArgs.empty())
            finalArgs += " ";
        finalArgs += tracker.removedArgs;
    }
        
    std::string modeMessage = ":" + client.getPrefix() + " " + this->_name + " " + chan.getName() + " " + finalModes;
    if (!finalArgs.empty())
        modeMessage += " " + finalArgs;
    modeMessage += "\r\n";
    chan.sendToChannel(modeMessage, this->_context.clients, -1);
}


