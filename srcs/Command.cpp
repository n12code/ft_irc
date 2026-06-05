/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:23:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/05 08:20:04 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "CommandContext.hpp"
#include <string>

Command::Command(CommandContext context, std::string name, RegRule rule, bool authRequired) :
    _context(context),
    _name(name),
    _rule(rule),
    _authRequired(authRequired) {}

Command::~Command() {}

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