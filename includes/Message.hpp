/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:38:55 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/02 10:38:37 by nbodin           ###   ########lyon.fr   */
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
        std::string     _src;
        std::string     _cmd;
        std::string     _params;

        static std::string     extractMessage(std::string& buffer);
        static std::string     extractSrc(std::string message);
        static std::string     extractCmd(std::string message);
        static std::string     extractParams(std::string message);
    public:
        Message(ClientManager& clients);
        ~Message();

        bool    readMessage(int fd);
        bool    parseMessage(std::string& buffer);
};

#endif