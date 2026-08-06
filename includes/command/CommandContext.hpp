/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:08:29 by ubuntu            #+#    #+#             */
/*   Updated: 2026/06/08 10:44:52 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDCONTEXT_HPP
# define COMMANDCONTEXT_HPP

class Server;
class Client;
class ClientManager;
class ChannelManager;
class Message;


struct CommandContext {
    Server&         server;
    Client&         client;
    ClientManager&  clients;
    ChannelManager& channels;
    Message&        msg;

    CommandContext(Server& s, Client& c, ClientManager& cm, ChannelManager& chm, Message& m);
};

#endif