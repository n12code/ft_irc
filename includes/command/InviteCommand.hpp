/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 07:48:19 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/19 07:51:00 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class InviteCommand : public Command
{
    public:
        InviteCommand(const CommandContext& context);
        ~InviteCommand();

        void    execute();
};

#endif