/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 09:54:16 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 08:53:35 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "TopicCommand.hpp"
#include "ChannelManager.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Replies.hpp"
#include <vector>
#include <string>

TopicCommand::TopicCommand(const CommandContext &context):
    Command(context, "TOPIC", POST_REG, 1, true) {}

TopicCommand::~TopicCommand() {}       

void TopicCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    
    if (!this->_context.channels.hasChannel(params[0]))
    {
        this->_context.client.sendMessage(Replies::create(ERR_NOSUCHCHANNEL, this->_context.client.getNick(), params[0]));
        return ;
    }
    Channel&    chan = this->_context.channels.getChannelByName(params[0]);
    if (!chan.isUser(this->_context.client.getFd()))
    {
        this->_context.client.sendMessage(Replies::create(ERR_NOTONCHANNEL, this->_context.client.getNick(), chan.getName()));
        return ;
    }
    if (params.size() >= 2)
    {
        if (chan.hasMode('t') && !chan.isChanop(this->_context.client.getFd()))
        {
            this->_context.client.sendMessage(Replies::create(ERR_CHANOPRIVSNEEDED, this->_context.client.getNick(), chan.getName()));
            return ;
        }
        if (isJustSpaces(params[1]))
        {
            if (chan.getTopic().empty())
            {
                this->_context.client.sendMessage(Replies::create(RPL_NOTOPIC, this->_context.client.getNick(), chan.getName()));
                return ;
            }
            chan.setTopic("");
        }
        else
            chan.setTopic(params[1]);
        std::string TopicMsg = ":" + this->_context.client.getPrefix() + " " + this->_name + " " + chan.getName() + " :" + chan.getTopic() + "\r\n";
        chan.sendToChannel(TopicMsg, this->_context.clients);
    }
    else
    {
        if (chan.getTopic().empty())
            this->_context.client.sendMessage(Replies::create(RPL_NOTOPIC, this->_context.client.getNick(), chan.getName()));
        else
            this->_context.client.sendMessage(Replies::create(RPL_TOPIC, this->_context.client.getNick(), chan.getName(), chan.getTopic()));
    }
}

bool TopicCommand::isJustSpaces(const std::string& str) const
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] != ' ')
            return (false);
    }
    return (true);
}
