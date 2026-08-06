/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 09:11:25 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:09:48 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command/PrivMsgCommand.hpp"
#include "Message.hpp"
#include "ChannelManager.hpp"
#include "Channel.hpp"
#include "ClientManager.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Status.hpp"

PrivMsgCommand::PrivMsgCommand(const CommandContext &context):
    Command(context, "PRIVMSG", POST_REG, 2, true) {}

PrivMsgCommand::~PrivMsgCommand() {}

void PrivMsgCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    std::vector<std::string>    targets = ParseParam(params[0]);
    std::string                 msg = params[1];

    if (targets.size() > 5)
    {
        this->_context.client.sendMessage(Replies::create(ERR_TOOMANYTARGETS, this->_context.client.getNick(), params[0]));
        return ;
    }
    for (size_t i = 0; i < targets.size(); ++i)
    {
        std::string PrivMsg = ":" + this->_context.client.getPrefix() + " " + this->_name + " " + targets[i] +  " :" + msg + "\r\n";  
        if (this->_context.channels.hasChannel(targets[i]))
        {
            Channel&    chan = this->_context.channels.getChannelByName(targets[i]);
            chan.sendToChannel(PrivMsg, this->_context.clients, this->_context.client.getFd());
        }
        else if (this->_context.clients.hasClient(targets[i]))
        {
            Client&     client = this->_context.clients.getClientWithNick(targets[i]);
            client.sendMessage(PrivMsg);
        }
        else
            this->_context.client.sendMessage(Replies::create(ERR_NOSUCHNICK, this->_context.client.getNick(), targets[i]));
    }
}
