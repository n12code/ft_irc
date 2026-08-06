/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:02:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 07:22:37 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "Command.hpp"

class NickCommand : public Command
{
    public:
        NickCommand(const CommandContext& context);
        ~NickCommand();

        void    execute();
        bool    isValidNick(const std::string &nick);
};

#endif