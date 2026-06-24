/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:51:03 by ubuntu            #+#    #+#             */
/*   Updated: 2026/06/24 09:57:49 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include "CommandContext.hpp"
#include "Message.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Status.hpp"
#include "Replies.hpp"
#include <iostream>

PassCommand::PassCommand(const CommandContext &context):
    Command(context, "PASS", PRE_REG, 1, false) {}

PassCommand::~PassCommand() {}

void    PassCommand::execute()
{
    if (this->_context.msg.getParams()[0] != this->_context.server.getPassword())
    {
        this->_context.client.sendMessage(Replies::create(ERR_PASSWDMISMATCH, "*"));
        return ;
    }
    this->_context.client.setAuth(true);
    std::cout << "PASS COMMAND authenticated" << std::endl;
}