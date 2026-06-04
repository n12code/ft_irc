/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:27:45 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 10:59:27 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDDISPATCHER_HPP
# define COMMANDDISPATCHER_HPP

# include <map>
# include <string>
# include "ClientManager.hpp"
# include "ChannelManager.hpp"

class Message;
class Command;

class CommandDispatcher
{
    private:
        std::map<std::string, Command*> _commands;
        ClientManager&                  _clients;
        //ChannelManager&                 _channels;
    public:
        CommandDispatcher(ClientManager& clients);//channel manager
        ~CommandDispatcher();

        void    dispatch(int clientFd, Message msg);
};

#endif