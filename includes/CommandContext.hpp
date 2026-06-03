/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:08:29 by ubuntu            #+#    #+#             */
/*   Updated: 2026/06/04 00:56:53 by ubuntu           ###   ########lyon.fr   */
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
    //ChannelManager& channels;
    const Message&  msg;

    CommandContext(Server& s, Client& c, ClientManager& cm, const Message& m);
};

#endif