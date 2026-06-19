/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 07:51:28 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/19 08:42:44 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCommand.hpp"
#include "ChannelManager.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Replies.hpp"
#include <vector>
#include <string>

InviteCommand::InviteCommand(const CommandContext &context):
    Command(context, "INVITE", POST_REG, 2, true) {}

InviteCommand::~InviteCommand() {}

void    InviteCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    if (!this->_context.clients.hasClient(params[0]))
    {
        this->_context.client.sendMessage(Replies::create(ERR_NOSUCHNICK, this->_context.client.getNick(), params[0]));
        return ;
    }
    Client& client = this->_context.clients.getClientWithNick(params[0]);
    if (this->_context.channels.hasChannel(params[1]))
    {
        Channel&    chan = this->_context.channels.getChannelByName(params[1]);
        if (!chan.isUser(this->_context.client.getFd()))
        {
            this->_context.client.sendMessage(Replies::create(ERR_NOTONCHANNEL, this->_context.client.getNick(), params[1]));
            return ;
        }
        if (chan.hasMode('i') && !chan.isChanop(this->_context.client.getFd()))
        {
            this->_context.client.sendMessage(Replies::create(ERR_CHANOPRIVSNEEDED, this->_context.client.getNick(), params[1]));
            return ;
        }
        if (chan.isUser(client.getFd()))
        {
            this->_context.client.sendMessage(Replies::create(ERR_USERONCHANNEL, this->_context.client.getNick(), client.getNick(), params[1]));
            return ;
        }
        chan.addInvited(client.getFd());
    }
    std::string inviteMsg = ":" + this->_context.client.getPrefix() + " " + this->_name + " " + client.getNick() + " " + params[1] + "\r\n";
    client.sendMessage(inviteMsg);
    this->_context.client.sendMessage(Replies::create(RPL_INVITING, this->_context.client.getNick(), client.getNick(), params[1]));
}