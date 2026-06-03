/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:04:20 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 00:24:19 by ubuntu           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include "CommandContext.hpp"

class Message;
class ClientManager;
class ChannelManager;

class Command
{
    protected:
        CommandContext  _context;
        std::string     _name;
        bool            _authRequired;
    public:
        Command(CommandContext context, std::string name, bool authRequired = true);
        virtual ~Command();

        virtual void    execute() = 0;
        std::string&    getName();
        bool            isAuthRequired();
};

#endif