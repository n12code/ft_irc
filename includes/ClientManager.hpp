/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:54:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/05 11:25:46 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMANAGER_HPP
# define CLIENTMANAGER_HPP

# include <map>
# include <string>

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

        //utility
        bool    isNickInUse(const std::string& nick) const;
};

#endif