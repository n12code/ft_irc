/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:47:43 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/15 08:04:42 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
    private:
        int             _fd;
        bool            _auth;
        bool            _registered;
        std::string     _buffer;
        std::string     _nick;
        std::string     _user;
        std::string     _host;
        std::string     _prefix;
    public:
        Client();
        Client(int fd); 
        Client(const Client& copy); 
        ~Client();
        
        //getter
        int&                getFd();
        bool                isRegistered();
        bool                isAuth();
        std::string&        getBuffer();
        const std::string&  getNick() const;
        const std::string&  getUser() const;
        const std::string&  getHost() const;
        const std::string&  getPrefix() const;

        void                setAuth(bool auth);
        void                setNick(const std::string& nick);
        void                setUser(const std::string& user);
        void                setHost(const std::string& host);
        void                setPrefix(const std::string& host);
        void                setRegistered(bool registered);
        
        void                sendMessage(const std::string& message) const;
};

#endif