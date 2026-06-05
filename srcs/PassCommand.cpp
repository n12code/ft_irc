/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:51:03 by ubuntu            #+#    #+#             */
/*   Updated: 2026/06/05 10:12:29 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include <iostream>

PassCommand::PassCommand(const CommandContext &context):
    Command(context, "PASS", PRE_REG, 1, false) {}

PassCommand::~PassCommand() {}

void    PassCommand::execute()
{
    std::cout << "pass" << std::endl;
}