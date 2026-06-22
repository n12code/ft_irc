/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 09:47:57 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 08:58:17 by nbodin           ###   ########lyon.fr   */
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
    return (":" +  _server + " 400 :Unknown error\r\n");
}

void Replies::init()
{
    _server = ":localhost";
    //errors
    _replies[ERR_NOTREGISTERED] = errNotRegistered;
    _replies[ERR_NEEDMOREPARAMS] = errNeedMoreParams;
    _replies[ERR_ALREADYREGISTERED] = errAlreadyRegistered;
    _replies[ERR_ERRONEUSNICKNAME] = errErroneusNickName;
    _replies[ERR_NICKNAMEINUSE] = errNickNameInUse;
    _replies[ERR_PASSWDMISMATCH] = errPasswdMismatch;
    _replies[ERR_NOSUCHNICK] = errNoSuchNick;
    _replies[ERR_NOSUCHCHANNEL] = errNoSuchChannel;
    _replies[ERR_USERNOTINCHANNEL] = errUserNotInChannel;
    _replies[ERR_NOTONCHANNEL] = errNotOnChannel;
    _replies[ERR_USERONCHANNEL] = errUserOnChannel;
    _replies[ERR_KEYSET] = errKeySet;
    _replies[ERR_CHANNELISFULL] = errChannelIsFull;
    _replies[ERR_UNKNOWNMODE] = errUnknownMode;
    _replies[ERR_INVITEONLYCHAN] = errInviteOnlyChan;
    _replies[ERR_BADCHANNELKEY] = errBadChannelKey;
    _replies[ERR_CHANOPRIVSNEEDED] = errChaNoPrivsNeeded;

    //replies
    _replies[RPL_WELCOME] = rplWelcome;
    _replies[RPL_ENDOFWHO] = rplEndOfWho;
    _replies[RPL_CHANNELMODEIS] = rplChannelModeIs;
    _replies[RPL_NOTOPIC] = rplNoTopic;
    _replies[RPL_TOPIC] = rplTopic;
    _replies[RPL_INVITING] = rplInviting;
    _replies[RPL_WHOREPLY] = rplWhoReply;
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
    std::string rep = _server + " 401 " + args[0] + " " + args[1] + " :No such nick/channel\r\n";
    return (rep);
}

std::string Replies::errNoSuchChannel(const std::vector<std::string> &args)
{
    std::string rep = _server + " 403 " + args[0] + " " + args[1] + " :No such channel\r\n";
    return (rep);
}

std::string Replies::errErroneusNickName(const std::vector<std::string> &args)
{
    std::string rep = _server + " 432 " + args[0] + " " + args[1] + " :Erroneous nickname\r\n";
    return (rep);
}

std::string Replies::errNickNameInUse(const std::vector<std::string> &args)
{
    std::string rep = _server + " 433 " + args[0] + " " + args[1] + " :Nickname is already in use\r\n";
    return (rep);
}

std::string Replies::errUserNotInChannel(const std::vector<std::string> &args)
{
    std::string rep = _server + " 441 " + args[0] + " " + args[1] + " " + args[2] + " :They aren't on that channel\r\n";
    return (rep);
}

std::string Replies::errNotOnChannel(const std::vector<std::string> &args)
{
    std::string rep = _server + " 442 " + args[0] + " " + args[1] + " :You're not on that channel\r\n";
    return (rep);
}

std::string Replies::errUserOnChannel(const std::vector<std::string> &args)
{
    std::string rep = _server + " 443 " + args[0] + " " + args[1] + " " + args[2] + " :is already on channel\r\n";
    return (rep);
}

std::string Replies::errNotRegistered(const std::vector<std::string> &args)
{
    std::string rep = _server + " 451 " + args[0] + ":You have not registered\r\n";//do i even need arg[0]?
    return (rep);
}

std::string Replies::errNeedMoreParams(const std::vector<std::string> &args)
{
    std::string rep = _server + " 461 " + args[0] + " "  + args[1] + " :Not enough parameters\r\n";
    return (rep);
}

std::string Replies::errAlreadyRegistered(const std::vector<std::string> &args)
{
    std::string rep = _server + " 462 " + args[0] + ":Unauthorized command (already registered)\r\n";//do i even need arg[0]?
    return (rep);
}

std::string Replies::errPasswdMismatch(const std::vector<std::string> &args)
{
    std::string rep = _server + " 464 " + args[0] + ":Password incorrect\r\n";//do i even need arg[0]?
    return (rep);
}

std::string Replies::errKeySet(const std::vector<std::string> &args)
{
    std::string rep = _server + " 467 " + args[0] + " " + args[1] + " :Channel key already set\r\n";
    return (rep);
}

std::string Replies::errChannelIsFull(const std::vector<std::string> &args)
{
    std::string rep = _server + " 471 " + args[0] + " " + args[1] + " :Cannot join channel (+l)\r\n";
    return (rep);
}

std::string Replies::errUnknownMode(const std::vector<std::string> &args)
{
    std::string rep = _server + " 472 " + args[0] + " " + args[1] + " :is unknown mode char to me for " + args[2] + "\r\n";
    return (rep);
}

std::string Replies::errInviteOnlyChan(const std::vector<std::string> &args)
{
    std::string rep = _server + " 473 " + args[0] + " " + args[1] + " :Cannot join channel (+i)\r\n";
    return (rep);
}

std::string Replies::errBadChannelKey(const std::vector<std::string> &args)
{
    std::string rep = _server + " 475 " + args[0] + " " + args[1] + " :Cannot join channel (+k)\r\n";
    return (rep);
}

std::string Replies::errChaNoPrivsNeeded(const std::vector<std::string> &args)
{
    std::string rep = _server + " 482 " + args[0] + " " + args[1] + " :You're not channel operator\r\n";
    return (rep);
}

// replies
std::string Replies::rplWelcome(const std::vector<std::string> &args)
{
    std::string rep = _server + " 001 " + args[0] + " :Welcome to the Internet Relay Network " + args[1] + "\r\n";
    return (rep);
}

std::string Replies::rplEndOfWho(const std::vector<std::string> &args)
{
    std::string rep = _server + " 315 " + args[0] + " " + args[1] + " :End of WHO list\r\n";
    return (rep);
}

std::string Replies::rplChannelModeIs(const std::vector<std::string> &args)
{
    std::string rep = _server + " 324 " + args[0] + " " + args[1] + " " + args[2] + args[3] + "\r\n";
    return (rep);
}

std::string Replies::rplNoTopic(const std::vector<std::string> &args)
{
    std::string rep = _server + " 331 " + args[0] +  " " + args[1] +  " :No topic is set\r\n";
    return (rep);
}

std::string Replies::rplTopic(const std::vector<std::string> &args)
{
    std::string rep = _server + " 332 " + args[0] +  " " + args[1] +  " :" + args[2] + "\r\n";
    return (rep);
}

std::string Replies::rplInviting(const std::vector<std::string> &args)
{
    std::string rep = _server + " 341 " + args[0] +  " " + args[1] +  " " + args[2] + "\r\n";
    return (rep);
}

std::string Replies::rplWhoReply(const std::vector<std::string> &args)
{
    std::string rep = _server + " 352 " + args[0] + " " + args[1] + " " + args[2] + " " + args[3] + " " + _server + " " + args[4] + " H" + args[5] + " :0 " + args[6] + "\r\n";
    return (rep);
}

std::string Replies::rplNamReply(const std::vector<std::string> &args)
{
    std::string rep = _server + " 353 " + args[0] + " " + args[1] + " :" + args[2] + "\r\n";
    return (rep);
}

std::string Replies::rplEndOfNames(const std::vector<std::string> &args)
{
    std::string rep = _server + " 366 " + args[0] + " " + args[1] + " :End of NAMES list\r\n";
    return (rep);
}
