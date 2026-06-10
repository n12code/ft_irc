/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:11:14 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/10 10:57:19 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "Command.hpp"
# include "Status.hpp"
# include <string>

class Channel;
class Client;

class JoinCommand : public Command
{
    public:
        JoinCommand(const CommandContext& context);
        ~JoinCommand();

        void    execute();
        Status     join(Channel* channel, const std::string& passwd, const int clientFd);
        Status     isValidName(std::string& name);
        void    sendMessages(Channel* channel, Client& client);
};

#endif