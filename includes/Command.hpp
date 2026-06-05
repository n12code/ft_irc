/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:04:20 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/05 08:20:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include "CommandContext.hpp"

class Message;
class ClientManager;
class ChannelManager;

enum RegRule {
    PRE_REG,
    POST_REG,
    ANYTIME
};

class Command
{
    protected:
        CommandContext  _context;
        std::string     _name;
        RegRule         _rule;
        bool            _authRequired;
    public:
        Command(CommandContext context, std::string name, RegRule rule, bool authRequired = true);
        virtual ~Command();

        virtual void    execute() = 0;
        std::string&    getName();
        RegRule         getRule();
        bool            isAuthRequired();
};

#endif