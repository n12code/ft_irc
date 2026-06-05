/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:23:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/05 10:09:51 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "CommandContext.hpp"
#include <string>

Command::Command(CommandContext context, std::string name, RegRule rule, size_t minParams, bool authRequired) :
    _context(context),
    _name(name),
    _rule(rule),
    _minParams(minParams),
    _authRequired(authRequired) {}

Command::~Command() {}

CommandContext&  Command::getContext()
{
    return(this->_context);
}

std::string&    Command::getName()
{
    return (this->_name);
}

RegRule Command::getRule()
{
    return (this->_rule);
}

bool    Command::isAuthRequired() 
{
    return (this->_authRequired);
}

size_t  Command::getMinParams()
{
    return (this->_minParams);
}