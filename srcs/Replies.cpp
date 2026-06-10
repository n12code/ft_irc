/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 09:47:57 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/10 10:44:38 by nbodin           ###   ########lyon.fr   */
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
}

std::string Replies::create(Status status, const std::string &arg1, const std::string &arg2, const std::string &arg3, const std::string &arg4, const std::string &arg5, const std::string &arg6, const std::string &arg7, const std::string &arg8)
{
    std::vector<std::string>    args;
    const   std::string         optArgs[] = {arg2, arg3, arg4, arg5, arg6, arg7, arg8};
    size_t                      nbOfOptArgs = 7;

    
    args.push_back(arg1);
    for (size_t i = 0; i < nbOfOptArgs; ++i)
    {
        if (!optArgs[i].empty())
            args.push_back(optArgs[i]);
    }
    return (dispatch(status, args));
}

//messages
std::string Replies::errNoSuchChannel(const std::vector<std::string> &args)
{
    std::string rep = "403 ERR_NOSUCHCHANNEL " + args[0] + " :No such channel\r\n";
    return (rep);
}