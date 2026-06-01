/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:54:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/01 10:22:29 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMANAGER_HPP
# define CLIENTMANAGER_HPP

# include <map>

class Client;

class ClientManager
{
    private:
        std::map<int, Client>   _clients;
    public:
        ClientManager();
        ~ClientManager();

        //getter
        Client& getClientWithFd(int fd);

        //setter
        void    addClient(Client client);
        void    removeClient(int fd);

};

#endif