/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 09:11:45 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/11 09:17:33 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class PartCommand : public Command
{
    public:
        PartCommand(const CommandContext context);
        ~PartCommand();

        void    execute();
};




#endif