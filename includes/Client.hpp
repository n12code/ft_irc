/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:47:43 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/05 10:26:13 by nbodin           ###   ########lyon.fr   */
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
    public:
        Client();
        Client(int fd); 
        Client(const Client& copy); 
        ~Client();
        
        //getter
        int&            getFd();
        bool            isRegistered();
        bool            isAuth();
        std::string&    getBuffer();
        std::string&    getNick();
        std::string&    getUser();

        void            setAuth(bool auth);
};

#endif