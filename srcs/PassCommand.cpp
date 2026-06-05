/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:51:03 by ubuntu            #+#    #+#             */
/*   Updated: 2026/06/05 10:28:56 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include "CommandContext.hpp"
#include "Message.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>

PassCommand::PassCommand(const CommandContext &context):
    Command(context, "PASS", PRE_REG, 1, false) {}

PassCommand::~PassCommand() {}

void    PassCommand::execute()
{
    if (this->_context.msg.getParams()[0] != this->_context.server.getPassword())
    {
        std::cout << "464 password mismatch" << std::endl;
        return ;
    }
    this->_context.client.setAuth(true);
    std::cout << "authenticated" << std::endl;
}