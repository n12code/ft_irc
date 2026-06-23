/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:47:43 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 11:02:07 by nbodin           ###   ########lyon.fr   */
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
        std::string     _msgBuffer;
        std::string     _nick;
        std::string     _user;
        std::string     _realname;
        std::string     _host;
        std::string     _prefix;
    public:
        Client();
        Client(int fd); 
        ~Client();
        
        int&                getFd();
        bool                isRegistered();
        bool                isAuth();
        const std::string&  getBuffer() const;
        std::string&        getBuffer();
        const std::string&  getNick() const;
        const std::string&  getUser() const;
        const std::string&  getHost() const;
        const std::string&  getPrefix() const;
        const std::string&  getRealName() const;

        void                setAuth(bool auth);
        void                setNick(const std::string& nick);
        void                setUser(const std::string& user);
        void                setHost(const std::string& host);
        void                setPrefix(const std::string& host);
        void                setRealName(const std::string& realname);
        void                setRegistered(bool registered);
        
        void                sendMessage(const std::string& message);
        void                appendToBuffer(std::string& buffer, const std::string& str);
};

#endif