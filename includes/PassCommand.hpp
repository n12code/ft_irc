/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:02:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 00:51:42 by ubuntu           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCOMMAND_HPP
# define PASSCOMMAND_HPP

#include "Command.hpp"

class PassCommand : public Command
{
    public:
        PassCommand(const CommandContext& context);
        ~PassCommand();

        void execute();
};

#endif