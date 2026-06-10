/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:12:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/10 11:02:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "ChannelManager.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Replies.hpp"
#include <iostream>

JoinCommand::JoinCommand(const CommandContext& context):
    Command(context, "JOIN", POST_REG, 1, true) {}

JoinCommand::~JoinCommand() {}

// ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
// ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
// ERR_CHANNELISFULL               ERR_BADCHANMASK
// ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
// ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
// RPL_TOPIC

void JoinCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams(); 
    std::vector<std::string>    channels = ParseParam(params[0]);
    std::vector<std::string>    keys;
    if (params.size() >= 2)
        keys = ParseParam(params[1]);
    if (channels[0] == "0")
    {
        //PART for every channels
        return ;
    }
    else
    {
        std::string pass;
        Status      status;
        Client&     client = this->_context.client;
        for (size_t i = 0; i < channels.size(); ++i)
        {
            Channel*    chan = NULL;
            pass = i < keys.size() ? keys[i] : "";;
            if (this->_context.channels.hasChannel(channels[i]))
            {
                std::cout << "joining" << std::endl;
                chan = &this->_context.channels.getChannelByName(channels[i]);
                status = this->join(chan, pass, client.getFd());
                if (status != SUCCESS)
                {
                    client.sendMessage(Replies::create(status, channels[i]));
                    continue ;
                }
            }
            else
            {
                std::cout << "creation" << std::endl;
                status = isValidName(channels[i]);
                if (status != SUCCESS)
                {
                    client.sendMessage(Replies::create(status, channels[i]));
                    continue ;
                }
                chan = &this->_context.channels.createChannel(channels[i], client.getFd());
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
    if (channel->hasMode('l') && channel->getMaxCap() == channel->getUsers().size())
        return (ERR_CHANNELISFULL);
    channel->addUser(clientFd);
    return (SUCCESS);
}

Status JoinCommand::isValidName(std::string& name)
{
    std::cout << "name : " << name << std::endl;
    if (name.empty() ||
        name.size() > 50 ||
        (name[0] != '#' &&
        name[0] != '&'))
        return (ERR_NOSUCHCHANNEL);

    Command::toLowerIRC(name);
    
    for (size_t i = 1; i < name.size(); ++i)
    {
        if (name[i] == '\a')
            return (ERR_NOSUCHCHANNEL);
    }
    return (SUCCESS);
}

void    JoinCommand::sendMessages(Channel* channel, Client& client)
{
    //JOIN msg
    std::string joinMsg = this->_name + " message from " + client.getNick() + " on channel " + channel->getName();
    std::cout << "joinMSG : " << joinMsg << std::endl;
    client.sendMessage(joinMsg);
    
    //RPL_TOPIC
    //client.sendMessage(Replies::rplTopic(channel.getTopic()));
    
    //RPL_NAMEREPLY
    // std::string     namesMsg;
    // std::set<int>   users = channel->getUsers();
    // ClientManager&  clients = this->_context.clients;
    // std::set<int>::const_iterator   it = users.begin();
    // for (; it != users.end(); ++it)
    // {
    //     if (channel->isChanop(*it))
    //         namesMsg += "@";
    //     namesMsg += clients.getClientWithFd(*it).getNick() + " ";
    // }
    //client.sendMessage(Replies::rplNamReply("=" + channel->getName(), namesMsg));

    //RPL_ENDOFNAMES
    //client.sendMessage(Replies::rplEndOfNames(channel->getName()));
}