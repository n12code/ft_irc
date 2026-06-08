/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:11:14 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 10:12:41 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "Command.hpp"

class JoinCommand : public Command
{
    public:
        JoinCommand(const CommandContext& context);
        ~JoinCommand();

        void    execute();
};


#endif