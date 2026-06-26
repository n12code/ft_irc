/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 08:48:37 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/26 09:11:20 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <exception>
#include <sstream>
#include <signal.h>
#include <csignal>

//check for private/protected/public scopes for classes,methods/functions,member variables
//check for only necessary constructors and operators
//check for good organisation of methods
//check for const identifiers
//check for references
//check for const for return types and arguments

volatile std::sig_atomic_t g_quit = 0;

void    handleSigInt(int sig)
{
    if (sig == SIGINT)
        g_quit = 1;
}   

void    handleSignal()
{
    struct sigaction    sa = {};
    sa.sa_handler = handleSigInt;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}

int main(int argc, char *argv[])
{
    Server *server = NULL;
    try {
        if (argc != 3)
        {
            std::cerr << "Error: Please precise the port number and then the password" << std::endl;
            return (1);
        }
        
        std::istringstream   ss(argv[1]);
        unsigned short port;
        if (!(ss >> port) || !ss.eof())
        {
            std::cerr << "Error: Please precise a valid port number" << std::endl;
            return (1);
        }

        handleSignal();
        server = new Server(port, argv[2]);
        server->run();
        delete server;
    }
    catch (const std::exception &e) 
    {
        if (server)
        {
            if (server->getLoop().getEpfd() != -1)
                close(server->getLoop().getEpfd());
            server->getLoop().clearHandlers();
            delete server;
        }
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}