/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:12:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 11:35:35 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "ChannelManager.hpp"
#include "Message.hpp"
#include "Channel.hpp"

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
    if (!params.size() >= 2)
        std::vector<std::string>    keys = ParseParam(params[1]);
    if (channels[0] == "0")
    {
        //PART for every channels
        return ;
    }
    else
    {
        //join channels
        for (size_t i = 0; i < channels.size(); ++i)
        {
            if (this->_context.channels.hasChannel(channels[i]))
            {
                //join
            }
            else {
                //create
            }
        }
        
    }
    }
    
    //if params == 1
        //if param[0] == '0', PART for all channels
        //else join channel(s)
    //if params == 2
        //match key(s) and channel(s)
    //if channel exists, join
    //else, create
    //if successful
        //send RPL_TOPIC and RPL_NAMEREPLY/RPL_ENDOFNAMES
}