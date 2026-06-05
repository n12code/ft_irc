/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 08:48:37 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/05 11:12:45 by nbodin           ###   ########lyon.fr   */
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