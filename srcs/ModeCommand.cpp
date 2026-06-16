/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:33:22 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/16 11:04:59 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCommand.hpp"
#include "Message.hpp"
#include "ChannelManager.hpp"
#include "Channel.hpp"
#include "ClientManager.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Status.hpp"

ModeCommand::ModeCommand(const CommandContext &context):
    Command(context, "MODE", POST_REG, 1, true) {}

ModeCommand::~ModeCommand() {}

//ERR_CHANOPRIVSNEEDED

// ERR_NEEDMOREPARAMS              ERR_KEYSET                 
// ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE

// RPL_CHANNELMODEIS

// RPL_BANLIST                     RPL_ENDOFBANLIST
// RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
// RPL_INVITELIST                  RPL_ENDOFINVITELIST

// RPL_UNIQOPIS

void    ModeCommand::execute()
{
    std::vector<std::string>    params = this->_context.msg.getParams();
    bool                        adding = false;
    size_t                      totalArgModes = 0;
    size_t                      nbMode = 0;

    if (!this->_context.channels.hasChannel(params[0]))
    {
        //NOSUCHCHANNEL
        return ;   
    }

    Channel&    chan = this->_context.channels.getChannelByName(params[0]);
    params.erase(params.begin());
    if (params.size() == 0)
    {   
        //QUERY
        return ;
    }
    
    if (!chan.isChanop(this->_context.client.getFd()))
    {
        //CHANOPRIVSNEEDED
        return ;
    }
    for (size_t i = 0; i < params.size(); ++i)
    {
        //mode block
        if (params[i][0] == '+' || params[i][0] == '-')
        {
            for (size_t j = 0; j < params[i].size(); ++j)
            {
                char    c = params[i][j];
                if (c == '+')
                {
                    adding = true;
                    nbMode = 0;
                }
                else if (c == '-')
                {
                    adding = false;
                    nbMode = 0;
                }
                else if (c == 'k' || c == 'o' || (c == 'l' && adding))
                {
                    if (totalArgModes >= 3)
                        break ;
                    totalArgModes++;
                    nbMode++;
                    std::string arg = params[i + nbMode];
                    if (arg.empty())
                        // ERR_NEEDMOREPARAMS, return ?
                    if (adding)
                    {
                        //handle adding keys and privs and limit
                        if (c == 'k')
                        {
                            if (!chan.hasMode('k'))
                                //ERR_KEYSET, continue
                            chan.setPassword(arg);
                            chan.addMode('k');
                        }
                        else if (c == 'o')
                        {
                            if (!this->_context.clients.hasClient(arg));
                                //NOSUCHNICK?
                            int clientFd = this->_context.clients.getClientWithNick(arg).getFd();
                            if (!chan.isUser(clientFd))
                                //USERNOTINCHANNEL, continue
                            chan.addChanop(clientFd);
                        }
                        else
                        {
                            //handle limit adding
                        }
                    }
                    else
                    {
                        if (c == 'k')
                        {
                            chan.setPassword("");
                            chan.removeMode('k');
                        }
                        else if (c == 'o')
                        {
                            if (!this->_context.clients.hasClient(arg));
                                //NOSUCHNICK?
                            int clientFd = this->_context.clients.getClientWithNick(arg).getFd();
                            if (!chan.isUser(clientFd))
                                //USERNOTINCHANNEL, continue
                            chan.removeChanop(clientFd);
                        }
                    }
                }
                else if (c == 'i' || c == 't' || c == 'l' && !adding)
                {
                    if (adding)
                        //handle adding invite and topic
                    else
                        //handle removing invite and topic and limit
                }
                else
                    //unknowmode ? rturn ?
            }   
        }
        //skip
        else
        {
            if (i == 0)
                //unknown mode ?
                //return ?
        }
    }
}

