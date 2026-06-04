/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:38:55 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 11:02:30 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

# include "ClientManager.hpp"

class Message
{
    private:
        ClientManager&              _clients;
        std::string                 _source;//needed ?
        std::string                 _command;
        std::vector<std::string>    _params;
        std::string                 _trailing;

        std::string     extractMessage(std::string& buffer);
        void            extractCommand(std::string message);
        void            extractParams(std::string message);
    public:
        Message(ClientManager& clients);
        ~Message();

        bool    readMessage(int fd);
        bool    parseMessage(std::string& buffer);
        void    clearParsedData();

        //getter
        std::string&                getCommand();
        std::string&                getTrailing();
        std::vector<std::string>&   getParams();
};

#endif