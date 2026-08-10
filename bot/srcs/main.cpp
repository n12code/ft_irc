#include "Bot.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sstream>

int parse_ip(const std::string& ip_port, std::string& ip, unsigned short& port)
{
    size_t colon = ip_port.find(':');
    if (colon == std::string::npos)
        return (-1);

    ip = ip_port.substr(0, colon);

    std::istringstream ss(ip_port.substr(colon + 1));
    if (!(ss >> port) || !ss.eof())
        return (-1);

    return (0);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
        return (-1);

    std::string    ip;
    unsigned short port;
    std::string password(argv[2]);
    std::string user_name(argv[3]);
    std::string nick_name(argv[4]);
    
    if (parse_ip(argv[1], ip, port) == -1)
    {
        std::cerr << "Adresse invalide, format attendu : IP:PORT" << std::endl;
        return (-1);
    }

    int socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
        return (-1);

    sockaddr_in addr;
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) != 1)
    {
        std::cerr << "Invalid Ip Adress" << std::endl;
        return (-1);
    }

    if (::connect(socketFd, reinterpret_cast <sockaddr*> (&addr), sizeof(addr)) == -1)
    {
        if (errno != EINPROGRESS)
        {
            std::cerr << "connect failed: " << strerror(errno) << std::endl;
            return (-1);
        }
    }

    Bot bot(user_name, nick_name, socketFd);
    bot.connexion(password);

    while (true)
    {
        char buff[4096];
        ssize_t bytes = recv(socketFd, buff, sizeof(buff), 0);
        if (bytes <= 0)
            break;
        bot.handleIncoming(buff, bytes);
    }
    close(socketFd);
}