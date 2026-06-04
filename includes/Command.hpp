/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:04:20 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 11:17:11 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>

class Message;
class ClientManager;
class ChannelManager;

class Command
{
    private:
        std::string _name;
        bool        _authRequired;
    public:
        Command(std::string name, bool authRequired = true);
        virtual ~Command();

        virtual void    execute(int clientFd, Message msg, ClientManager& clients) = 0;//channel manager
        std::string&    getName();
        bool            isAuthRequired();
};

#endif