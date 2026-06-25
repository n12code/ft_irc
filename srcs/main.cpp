/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 08:48:37 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/25 08:30:16 by nbodin           ###   ########lyon.fr   */
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
//channel and nick case sensitive
//leaks
//check every comment
//has fd for client manager     
//PING?
//test with nc (ctrl+z fg, partial command ctrl d)
//ctrl c/ ctrl d
//check every std::cout/logging//std::cerr

//exception for a single client stops the server, watch for your try/catch and excpetions

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
    handleSignal();
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