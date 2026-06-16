/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 10:34:27 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/16 08:57:55 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "WhoCommand.hpp"
#include "Message.hpp"
#include "ChannelManager.hpp"
#include "Channel.hpp"
#include "ClientManager.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Status.hpp"

WhoCommand::WhoCommand(const CommandContext& context):
    Command(context, "WHO", POST_REG, 0, true) {}

WhoCommand::~WhoCommand() {}

void    WhoCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    std::string                 mask = (params.size() > 0) ? params[0] : "*";

    if (this->_context.channels.hasChannel(mask))
    {
        Channel&                        chan = this->_context.channels.getChannelByName(mask);
        Client*                         client = NULL;
        std::set<int>                   users = chan.getUsers();
        std::set<int>::const_iterator   it = users.begin();
        for (; it != users.end(); ++it)
        {
            client = &this->_context.clients.getClientWithFd(*it);
            std::string priv = (chan.isChanop(*it)) ? "@" : "";
            this->_context.client.sendMessage(Replies::create(RPL_WHOREPLY, this->_context.client.getNick(), chan.getName(), client->getUser(), client->getHost(), client->getNick(), priv, client->getRealName()));
        }
    }
    else if (this->_context.clients.hasClient(mask))
    {
        Client& client = this->_context.clients.getClientWithNick(mask);
        this->_context.client.sendMessage(Replies::create(RPL_WHOREPLY, this->_context.client.getNick(), "*", client.getUser(), client.getHost(), client.getNick(), "", client.getRealName()));
    }
    else if (mask == "*")
    {
        const std::map<int, Client>&          clients = this->_context.clients.getClients();
        std::map<int, Client>::const_iterator it = clients.begin();
        for (; it != clients.end(); ++it)
            this->_context.client.sendMessage(Replies::create(RPL_WHOREPLY, this->_context.client.getNick(), "*", it->second.getUser(), it->second.getHost(), it->second.getNick(), "", it->second.getRealName()));
    }
    this->_context.client.sendMessage(Replies::create(RPL_ENDOFWHO, this->_context.client.getNick(), mask));
}