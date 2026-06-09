/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:12:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/09 11:01:16 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "ChannelManager.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "Status.hpp"
#include "Client.hpp"
#include "Server.hpp"
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
    if (!params.size() >= 2)
        keys = ParseParam(params[1]);
    if (channels[0] == "0")
    {
        //PART for every channels
        return ;
    }
    else
    {
        std::string pass;
        int         status;
        Client&     client = this->_context.client;
        for (size_t i = 0; i < channels.size(); ++i)
        {
            Channel*    chan = NULL;
            pass = i < keys.size() ? keys[i] : "";;
            if (this->_context.channels.hasChannel(channels[i]))
            {
                chan = &this->_context.channels.getChannelByName(channels[i]);
                status = this->join(chan, pass, client.getFd());
                if (status != SUCCESS)
                {
                    std::cout << status << std::endl;
                    continue ;
                }
            }
            else
            {
                status = isValidName(channels[i]);
                if (status != SUCCESS)
                {
                    std::cout << status << std::endl;
                    continue ;
                }
                chan = &Channel(channels[i], client.getFd());
                this->_context.channels.addChannel(*chan);
            }
            sendMessages(chan);
            //send JOIN message, RPL_TOPIC and RPL_NAMEREPLY/RPL_ENDOFNAMES
        }
    }
}

int JoinCommand::join(Channel* channel, const std::string& passwd, const int clientFd)
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

bool JoinCommand::isValidName(std::string& name)
{
    if (name.empty() ||
        name.size() > 50 ||
        name[0] != '#' ||
        name[0] != '&')
        return (ERR_NOSUCHCHANNEL);
    
    Command::toLowerIRC(name);
    
    for (size_t i = 1; i < name.size(); ++i)
    {
        if (name[i] == '\a' ||
            name[i] == ' ' ||
            name[i] == ',' ||
            name[i] == ':')
            return (ERR_NOSUCHCHANNEL);
    }
    return (SUCCESS);
}

void    JoinCommand::sendMessages(Channel* channel, Client& client)
{
    //JOIN msg
    //std::string joinMsg = this->_name + " message from " + client.getNick() + " on channel " + channel->getName();
    //client.sendMessage(joinMsg)
    
    //RPL_TOPIC
    //client.sendMessage(Replies::rplTopic(channel.getTopic()));
    
    //RPL_NAMEREPLY
    //RPL_ENDOFNAMES
}