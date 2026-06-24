/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:04:20 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/24 10:59:06 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>
# include "CommandContext.hpp"
# include "RegRule.hpp"

class Message;
class ClientManager;
class ChannelManager;

class Command
{
    protected:
        CommandContext  _context;
        std::string     _name;
        RegRule         _rule;
        size_t          _minParams;
        bool            _authRequired;
    public:
        Command(CommandContext context, std::string name, RegRule rule, size_t minParams, bool authRequired);
        virtual ~Command();

        virtual void                execute() = 0;
        std::vector<std::string>    ParseParam(const std::string& params);
        void                        toLowerIRC(std::string& string);
                
        CommandContext& getContext();
        std::string&    getName();
        RegRule         getRule();
        size_t          getMinParams();
        bool            isAuthRequired();
};

#endif