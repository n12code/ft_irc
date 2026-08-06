/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 09:10:55 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 09:11:19 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCOMMAND_HPP
# define PRIVMSGCOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class PrivMsgCommand : public Command
{
    public:
        PrivMsgCommand(const CommandContext& context);
        ~PrivMsgCommand();

        void    execute();
};

#endif