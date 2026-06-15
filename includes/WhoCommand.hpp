/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 10:30:54 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/15 10:33:46 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHOCOMMAND_HPP
# define WHOCOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class WhoCommand : public Command
{
    public:
        WhoCommand(const CommandContext& context);
        ~WhoCommand();

        void    execute();
    };

#endif