/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 09:13:43 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:12:42 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PartCommand.hpp"
#include "Command.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"

PartCommand::PartCommand(const CommandContext context):
    Command(context, "PART", POST_REG, 1, true) {}

PartCommand::~PartCommand() {}

void    PartCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    std::vector<std::string>    channels = ParseParam(params[0]);
    
    for (size_t i = 0; i < channels.size(); ++i)
    {
        Channel*    chan = NULL;
        Client&  client = this->_context.client;
        if (this->_context.channels.hasChannel(channels[i]))
        {
            chan = &this->_context.channels.getChannelByName(channels[i]);
            if (chan->isUser(client.getFd()))
            {
                std::string partMsg = ":" + client.getPrefix() + " " + this->getName() + " " + chan->getName() + " :";
                if (params.size() >= 2)
                    partMsg += params[1] + "\r\n";
                else
                    partMsg += this->_context.client.getNick() + "\r\n";
                chan->sendToChannel(partMsg, this->_context.clients, -1);
                chan->removeUser(client.getFd());
                if (chan->getUsers().size() == 0)
                    this->_context.channels.removeChannel(chan->getName());
            }
            else
                client.sendMessage(Replies::create(ERR_NOTONCHANNEL, client.getNick(), chan->getName()));
        }
        else 
            client.sendMessage(Replies::create(ERR_NOSUCHCHANNEL, client.getNick(), channels[i]));
    }
}
