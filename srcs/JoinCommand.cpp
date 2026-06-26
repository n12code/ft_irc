/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:12:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/26 09:00:37 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "ChannelManager.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Replies.hpp"
#include "Utils.hpp"
#include <iostream>

JoinCommand::JoinCommand(const CommandContext& context):
    Command(context, "JOIN", POST_REG, 1, true) {}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    std::vector<std::string>    channels = ParseParam(params[0]);
    std::vector<std::string>    keys;
    if (params.size() >= 2)
        keys = ParseParam(params[1]);
    if (channels[0] == "0")
    {
        Command*    cmd = NULL;
        try
        {
            cmd = formatForPart();
            cmd->execute();
            delete cmd;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: error while executing [" << this->_name << "]: " << e.what() << std::endl;
            if (cmd != NULL)
                delete cmd;
        }
        return ;
    }
    else
    {
        std::string pass;
        Status      status;
        Client&     client = this->_context.client;
        Channel*    chan = NULL;
        for (size_t i = 0; i < channels.size(); ++i)
        {
            pass = i < keys.size() ? keys[i] : "";
            bool        isAlrMember = false;
            if (this->_context.channels.hasChannel(channels[i]))
            {
                chan = &this->_context.channels.getChannelByName(channels[i]);
                isAlrMember = chan->isUser(client.getFd());
                if (!isAlrMember)
                {
                    status = this->join(chan, pass, client.getFd());
                    if (status != SUCCESS)
                    {
                        client.sendMessage(Replies::create(status, client.getNick(), channels[i]));
                        continue ;
                    }
                    chan->removeInvited(client.getFd());
                }
            }
            else
            {
                status = isValidName(channels[i]);
                if (status != SUCCESS)
                {
                    client.sendMessage(Replies::create(status, client.getNick(), channels[i]));
                    continue ;
                }
                chan = &this->_context.channels.createChannel(channels[i], client.getFd());
            }   
            if (!isAlrMember)
            {
                std::string joinMsg = ":" + client.getPrefix() + " " + this->_name + " " + chan->getName() + "\r\n";
                client.sendMessage(joinMsg);
                chan->sendToChannel(joinMsg, this->_context.clients, client.getFd());
            }
            sendMessages(chan, client);
        }
    }
}

Status JoinCommand::join(Channel* channel, const std::string& passwd, const int clientFd)
{
    if (channel->hasMode('i') && !channel->isInvited(clientFd))
        return (ERR_INVITEONLYCHAN);
    if (channel->hasMode('k') && passwd != channel->getPassword())
        return (ERR_BADCHANNELKEY);
    if (channel->hasMode('l') && channel->getUsers().size() >= channel->getMaxCap())
        return (ERR_CHANNELISFULL);
    channel->addUser(clientFd);
    return (SUCCESS);
}

Status JoinCommand::isValidName(std::string& name)
{
    if (name.empty() ||
        name.size() > 50 ||
        (name[0] != '#' &&
        name[0] != '&'))
        return (ERR_NOSUCHCHANNEL);

    Utils::toLowerIrc(name);
    
    for (size_t i = 1; i < name.size(); ++i)
    {
        if (name[i] == '\a')
            return (ERR_NOSUCHCHANNEL);
    }
    return (SUCCESS);
}

void    JoinCommand::sendMessages(Channel* channel, Client& client)
{
    client.sendMessage(Replies::create(RPL_TOPIC, client.getNick(), channel->getName(), channel->getTopic()));
    
    std::string     namesMsg;
    std::set<int>   users = channel->getUsers();
    ClientManager&  clients = this->_context.clients;
    std::set<int>::const_iterator   it = users.begin();
    for (; it != users.end(); ++it)
    {
        if (channel->isChanop(*it))
            namesMsg += "@";
        namesMsg += clients.getClientWithFd(*it).getNick() + " ";
    }
    client.sendMessage(Replies::create(RPL_NAMREPLY, client.getNick(), "= " + channel->getName(), namesMsg));

    client.sendMessage(Replies::create(RPL_ENDOFNAMES, client.getNick(), channel->getName()));
}

Command*    JoinCommand::formatForPart()
{
    std::vector<std::string>    partParams;
    std::vector<std::string>    chanOfUser = this->_context.channels.getChannelsOfUser(this->_context.client.getFd());
    std::string                 newParam = "";
    
    for (size_t i = 0; i < chanOfUser.size(); ++i)
    {
        newParam += chanOfUser[i];
        if (i != chanOfUser.size() - 1)
            newParam += ",";
    }
    
    partParams.push_back(newParam);
    this->_context.msg.setParams(partParams);
    return (this->_context.server.getDispatcher().getCommands().at("PART")(this->_context));
}