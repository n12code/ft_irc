/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:28:29 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 11:04:36 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "CommandDispatcher.hpp"
#include "CommandContext.hpp"
#include "Message.hpp"
#include "PassCommand.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "JoinCommand.hpp"
#include "PartCommand.hpp"
#include "KickCommand.hpp"
#include "WhoCommand.hpp"
#include "ModeCommand.hpp"
#include "InviteCommand.hpp"
#include "TopicCommand.hpp"
#include "PrivMsgCommand.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <cctype>
#include <algorithm>
#include <iostream>

static Command* createPass(const CommandContext& context) { return new PassCommand(context); }
static Command* createNick(const CommandContext& context) { return new NickCommand(context); }
static Command* createUser(const CommandContext& context) { return new UserCommand(context); }
static Command* createJoin(const CommandContext& context) { return new JoinCommand(context); }
static Command* createPart(const CommandContext& context) { return new PartCommand(context); }
static Command* createKick(const CommandContext& context) { return new KickCommand(context); }
static Command* createWho(const CommandContext& context) { return new WhoCommand(context); }
static Command* createMode(const CommandContext& context) { return new ModeCommand(context); }
static Command* createInvite(const CommandContext& context) { return new InviteCommand(context); }
static Command* createTopic(const CommandContext& context) { return new TopicCommand(context); }
static Command* createPrivMsg(const CommandContext& context) { return new PrivMsgCommand(context); }

CommandDispatcher::CommandDispatcher(Server& server, ClientManager &clients, ChannelManager &channels) :
    _server(server),
    _clients(clients),
    _channels(channels)
{
    this->_commands["PASS"] = createPass;
    this->_commands["NICK"] = createNick;
    this->_commands["USER"] = createUser;
    this->_commands["JOIN"] = createJoin;
    this->_commands["PART"] = createPart;
    this->_commands["KICK"] = createKick;
    this->_commands["WHO"] = createWho;
    this->_commands["INVITE"] = createInvite;
    this->_commands["TOPIC"] = createTopic;
    this->_commands["MODE"] = createMode;
    this->_commands["PRIVMSG"] = createPrivMsg;
}

CommandDispatcher::~CommandDispatcher() {}

void    CommandDispatcher::dispatch(int clientFd, Message msg)
{
    std::string command = msg.getCommand();
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    Client&         client = this->_clients.getClientWithFd(clientFd);
    
    if (command == "QUIT")
        return ;//quit
    
    if (this->_commands.find(command) == this->_commands.end())
    {
        client.sendMessage(Replies::create(ERR_UNKNOWNCOMMAND, "*", command));
        return ;
    }
    
    CommandContext  context(this->_server, client, this->_clients, this->_channels, msg);
    Command*        cmd = this->_commands[command](context);
    RegRule         rule = cmd->getRule();
    Status          status = SUCCESS;
    
    if (rule == PRE_REG)
    {
        if (client.isRegistered())
            status = ERR_ALREADYREGISTERED;
        else if (cmd->isAuthRequired() && !client.isAuth())
            status = ERR_NOTREGISTERED;
    }
    else if (rule == POST_REG && !client.isRegistered())
        status = ERR_NOTREGISTERED;
    else if (rule == ANYTIME && !client.isAuth())
        status = ERR_NOTREGISTERED;

    if (status == SUCCESS && msg.getParams().size() < cmd->getMinParams())
        status = ERR_NOTREGISTERED;
        
    if (status != SUCCESS)
    {
        client.sendMessage(Replies::create(status, client.getNick(), command));
        delete (cmd);
        return ;
    }
    cmd->execute();
    delete (cmd);
}

const std::map<std::string, CommandDispatcher::CommandCreator>& CommandDispatcher::getCommands() const
{
    return (this->_commands);
}
