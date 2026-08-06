/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 08:26:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:13:08 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command/KickCommand.hpp"
#include "command/Command.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include "Status.hpp"
#include "Replies.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"

KickCommand::KickCommand(const CommandContext& context):
    Command(context, "KICK", POST_REG, 2, true) {}

KickCommand::~KickCommand() {}

void    KickCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    std::vector<std::string>    channels = ParseParam(params[0]);
    std::vector<std::string>    users = ParseParam(params[1]);
    std::string                 comment = this->_context.client.getNick();
    if (channels.size() > 1 && channels.size() != users.size())
    {
        this->_context.client.sendMessage(Replies::create(ERR_NEEDMOREPARAMS, this->_name));
        return ;
    }
    if (params.size() >= 3)
        comment = params[2];
    
    if (channels.size() == 1)
        handleOneChannel(channels, users, comment);
    else
        handleManyChannels(channels, users, comment);
}

void    KickCommand::handleManyChannels(const std::vector<std::string>& channels, const std::vector<std::string>& users, const std::string& comment)
{
    Channel*    chan = NULL;
    Client*     client = NULL;
    for (size_t i = 0; i < channels.size(); ++i)
    {
        if (this->_context.channels.hasChannel(channels[i]))
        {
            chan = &this->_context.channels.getChannelByName(channels[i]);
            if (chan->isUser(this->_context.client.getFd()))
            {
                if (chan->isChanop(this->_context.client.getFd()))
                {
                    if (this->_context.clients.hasClient(users[i]))
                    {
                        client = &this->_context.clients.getClientWithNick(users[i]);
                        if (chan->isUser(client->getFd()))
                        {   
                            std::string kickMsg = ":" + this->_context.client.getPrefix() + " " + this->_name + " " + chan->getName() + " " + client->getNick() + " :" + comment + "\r\n";
                            chan->sendToChannel(kickMsg, this->_context.clients, -1);
                            chan->removeUser(client->getFd());
                        }
                        else
                            this->_context.client.sendMessage(Replies::create(ERR_USERNOTINCHANNEL, this->_context.client.getNick(),client->getNick(), channels[i]));
                    }
                    else
                        this->_context.client.sendMessage(Replies::create(ERR_NOSUCHNICK, this->_context.client.getNick(), users[i]));
                }
                else
                    this->_context.client.sendMessage(Replies::create(ERR_CHANOPRIVSNEEDED, this->_context.client.getNick(), channels[i]));
            }
            else
                this->_context.client.sendMessage(Replies::create(ERR_NOTONCHANNEL, this->_context.client.getNick(), channels[i]));
        }
        else
            this->_context.client.sendMessage(Replies::create(ERR_NOSUCHCHANNEL, this->_context.client.getNick(), channels[i]));
    }
}

void    KickCommand::handleOneChannel(const std::vector<std::string>& channels, const std::vector<std::string>& users, const std::string& comment)
{
    if (this->_context.channels.hasChannel(channels[0]))
    {    
        Channel&    chan = this->_context.channels.getChannelByName(channels[0]);
        if (chan.isUser(this->_context.client.getFd()))
        {
            if (chan.isChanop(this->_context.client.getFd()))
            {
                Client* client = NULL;
                for (size_t i = 0; i < users.size(); ++i)
                {
                    if (this->_context.clients.hasClient(users[i]))
                    {
                        client = &this->_context.clients.getClientWithNick(users[i]);
                        if (chan.isUser(client->getFd()))
                        {   
                            std::string kickMsg = ":" + this->_context.client.getPrefix() + " " + this->_name + " " + chan.getName() + " " + client->getNick() + " :" + comment + "\r\n";
                            chan.sendToChannel(kickMsg, this->_context.clients, -1);
                            chan.removeUser(client->getFd());
                        }
                        else
                            this->_context.client.sendMessage(Replies::create(ERR_USERNOTINCHANNEL, this->_context.client.getNick(), client->getNick(), channels[0]));
                    }
                    else
                        this->_context.client.sendMessage(Replies::create(ERR_NOSUCHNICK, this->_context.client.getNick(), users[i]));
                }
            }
            else
                this->_context.client.sendMessage(Replies::create(ERR_CHANOPRIVSNEEDED, this->_context.client.getNick(), channels[0]));
        }
        else
            this->_context.client.sendMessage(Replies::create(ERR_NOTONCHANNEL, this->_context.client.getNick(), channels[0]));
    }
    else
        this->_context.client.sendMessage(Replies::create(ERR_NOSUCHCHANNEL, this->_context.client.getNick(),channels[0]));
}