/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:23:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 11:01:53 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include <string>


Command::Command(std::string name, bool authRequired) :
    _name(name),
    _authRequired(authRequired) {}

Command::~Command() {}

std::string&    Command::getName()
{
    return (this->_name);
}

bool    Command::isAuthRequired() 
{
    return (this->_authRequired);
}