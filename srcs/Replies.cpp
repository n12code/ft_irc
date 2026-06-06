/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 09:47:57 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/06 15:11:06 by ubuntu           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Replies.hpp"
#include <string>
#include <vector>
#include <iostream>

std::map<Status, Replies::ReplyBuilder> Replies::_replies;

std::string Replies::dispatch(Status status, const std::vector<std::string> &args)
{
    if (_replies.find(status) != _replies.end())
        return (_replies[status](args));
    return ("400 * :Unknown error\r\n");
}

void Replies::init()
{
    _replies[ERR_NOSUCHCHANNEL] = errNoSuchChannel;
    _replies[RPL_TOPIC] = rplTopic;
    _replies[RPL_NAMREPLY] = rplNamReply;
    _replies[RPL_ENDOFNAMES] = rplEndOfNames;
}

std::string Replies::create(Status status, const std::string &arg1, const std::string &arg2, const std::string &arg3, const std::string &arg4, const std::string &arg5, const std::string &arg6, const std::string &arg7, const std::string &arg8)
{
    std::vector<std::string>    args;
    const   std::string         argsArray[] = {arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8};
    size_t                      nbArgs = 8;

    for (size_t i = 0; i < nbArgs; ++i)
        args.push_back(argsArray[i]);
    return (dispatch(status, args));
}

//messages
std::string Replies::errNoSuchChannel(const std::vector<std::string> &args)
{
    std::string rep = "403 ERR_NOSUCHCHANNEL " + args[0] + " :No such channel\r\n";
    return (rep);
}

std::string Replies::rplTopic(const std::vector<std::string> &args)
{
    std::string rep = "332 RPL_TOPIC " + args[0] + " :" + args[1] + "\r\n";
    return (rep);
}

std::string Replies::rplNamReply(const std::vector<std::string> &args)
{
    std::string rep = "353 RPL_NAMREPLY " + args[0] + " :" + args[1] + "\r\n";
    return (rep);
}

std::string Replies::rplEndOfNames(const std::vector<std::string> &args)
{
    std::string rep = "366 RPL_ENDOFNAMES " + args[0] + " :End of NAMES list\r\n";
    return (rep);
}
