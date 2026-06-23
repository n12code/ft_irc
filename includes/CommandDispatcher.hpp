/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:27:45 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 08:02:05 by nbodin           ###   ########lyon.fr   */
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
class Server;
struct CommandContext;

class CommandDispatcher
{
    private:
        typedef Command* (*CommandCreator)(const CommandContext& ctx);
        std::map<std::string, CommandCreator>   _commands;
        Server&                                 _server;
        ClientManager&                          _clients;
        ChannelManager&                         _channels;
    public:
        CommandDispatcher(Server& server, ClientManager& clients, ChannelManager& channels);
        ~CommandDispatcher();

        bool                                            dispatch(int clientFd, Message msg);
        const std::map<std::string, CommandCreator>&    getCommands() const;
};

#endif