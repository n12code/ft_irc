/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 09:47:57 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/15 10:16:53 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Replies.hpp"
#include <string>
#include <vector>
#include <iostream>

std::map<Status, Replies::ReplyBuilder> Replies::_replies;
std::string Replies::_server;

std::string Replies::dispatch(Status status, const std::vector<std::string> &args)
{
    if (_replies.find(status) != _replies.end())
        return (_replies[status](args));
    return ("400 * :Unknown error\r\n");
}

void Replies::init()
{
    _server = "localhost";
    //errors
    _replies[ERR_NOSUCHNICK] = errNoSuchNick;
    _replies[ERR_NOSUCHCHANNEL] = errNoSuchChannel;
    _replies[ERR_USERNOTINCHANNEL] = errUserNotInChannel;
    _replies[ERR_NOTONCHANNEL] = errNotOnChannel;
    _replies[ERR_CHANNELISFULL] = errChannelIsFull;
    _replies[ERR_INVITEONLYCHAN] = errInviteOnlyChan;
    _replies[ERR_BADCHANNELKEY] = errBadChannelKey;
    _replies[ERR_CHANOPRIVSNEEDED] = errChaNoPrivsNeeded;

    //replies
    _replies[RPL_WELCOME] = rplWelcome;
    _replies[RPL_TOPIC] = rplTopic;
    _replies[RPL_NAMREPLY] = rplNamReply;
    _replies[RPL_ENDOFNAMES] = rplEndOfNames;
}

std::string Replies::create(Status status, const std::string &arg1, const std::string &arg2, const std::string &arg3, const std::string &arg4, const std::string &arg5, const std::string &arg6, const std::string &arg7, const std::string &arg8, const std::string &arg9)
{
    std::vector<std::string>    args;
    const   std::string         argsArray[] = {arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9};
    size_t                      nbArgs = 9;

    for (size_t i = 0; i < nbArgs; ++i)
        args.push_back(argsArray[i]);
    return (dispatch(status, args));
}

// errors

std::string Replies::errNoSuchNick(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 401 " + args[0] + " " + args[1] + " :No such nick/channel\r\n";
    return (rep);
}

std::string Replies::errNoSuchChannel(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 403 " + args[0] + " " + args[1] + " :No such channel\r\n";
    return (rep);
}
//done
std::string Replies::errUserNotInChannel(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 441 " + args[0] + " " + args[1] + " " + args[2] + " :They aren't on that channel\r\n";
    return (rep);
}

std::string Replies::errNotOnChannel(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 442 " + args[0] + " " + args[1] + " :You're not on that channel\r\n";
    return (rep);
}

std::string Replies::errChannelIsFull(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 471 " + args[0] + " " + args[1] + " :Cannot join channel (+l)\r\n";
    return (rep);
}

std::string Replies::errInviteOnlyChan(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 473 " + args[0] + " " + args[1] + " :Cannot join channel (+i)\r\n";
    return (rep);
}

std::string Replies::errBadChannelKey(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 475 " + args[0] + " " + args[1] + " :Cannot join channel (+k)\r\n";
    return (rep);
}

std::string Replies::errChaNoPrivsNeeded(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 482 " + args[0] + " " + args[1] + " :You're not channel operator\r\n";
    return (rep);
}

// replies
std::string Replies::rplWelcome(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 001 " + args[0] + " :Welcome to the Internet Relay Network " + args[1] + "\r\n";
    return (rep);
}

std::string Replies::rplTopic(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 332 " + args[0] +  " " + args[1] +  " :" + args[2] + "\r\n";
    return (rep);
}

std::string Replies::rplNamReply(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 353 " + args[0] + " " + args[1] + " :" + args[2] + "\r\n";
    return (rep);
}

std::string Replies::rplEndOfNames(const std::vector<std::string> &args)
{
    std::string rep = ":" + _server + " 366 " + args[0] + " " + args[1] + " :End of NAMES list\r\n";
    return (rep);
}
