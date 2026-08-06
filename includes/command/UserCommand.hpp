/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:20:54 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 08:05:01 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "Command.hpp"
# include <string>

class UserCommand : public Command
{
    public:
        UserCommand(const CommandContext& context);
        ~UserCommand();

        void    execute();
        void    FormatUser(std::string &user);
};

#endif