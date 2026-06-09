/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:11:14 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/09 11:00:15 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "Command.hpp"
# include "Status.hpp"
# include <string>

class JoinCommand : public Command
{
    public:
        JoinCommand(const CommandContext& context);
        ~JoinCommand();

        void    execute();
        int     join(Channel* channel, const std::string& passwd, const int clientFd);
        bool    isValidName(std::string& name);
        void    sendMessages(Channel* channel, Client& client);
};

#endif