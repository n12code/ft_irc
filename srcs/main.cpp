/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 08:48:37 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/12 11:04:00 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <exception>
#include <sstream>

//check for private/protected/public scopes
//check for const identifiers
//check for references
//check for const for return types and arguments
// \r and \0 remover
//channel and nick case sensitive
//leaks
//check status == replies functions
//check modes for join command once implemented
//15 settings max
//check every comment
//has nick, has fd for client manager, same logic as has name for channel manager -> no exception
//define server name for prefix
//handle source in message
//handle prefixes for replies and messages
//refacto replies format

int main(int argc, char *argv[])
{
    try {
        if (argc != 3)
            throw std::invalid_argument("Error: Please precise the port number and then the password");
        
        std::istringstream   ss(argv[1]);
        unsigned short port;
        if (!(ss >> port) || !ss.eof())
            throw std::invalid_argument("Error: Please precise a valid port number");
            
        Server server(port, argv[2]);
        server.run();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}