/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:38:55 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/02 08:28:00 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>

# include "ClientManager.hpp"

class Message
{
    private:
        ClientManager&  _clients;
    public:
        Message(ClientManager& clients);
        ~Message();

        bool readMessage(int fd);
        //parseMessage();
};

#endif