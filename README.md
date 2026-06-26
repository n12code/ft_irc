_This project has been created as part of the 42 curriculum by nbodin, lpalabos_

## Description  
The goal of this project is to implement a server that can communicate with clients, following the [IRC](https://en.wikipedia.org/wiki/IRC) protocol.  
This project was coded accordingly to the RFCs [1459](https://www.rfc-editor.org/info/rfc1459/), [2811](https://www.rfc-editor.org/info/rfc2811/) and [2812](https://www.rfc-editor.org/info/rfc2812/), as well as the [Modern IRC Docs](https://modern.ircdocs.horse/).  
We used HexChat as the reference client for our server.  
We implemented channel operators, [+itokl] for the channels modes, and the following commands:  
- PASS
- USER
- NICK
- JOIN
- PRIVMSG
- KICK
- INVITE
- TOPIC
- MODE
- WHO
- PART

## Instructions  
### Start the server
To run the project, do:  
```
make run
```  
This will start the server on the port 6667 on the localhost, the password to connect is `irc`.

### Connect to the server
#### Terminal
You can either connect to the server using your terminal like the following:
```
~nc -C 127.0.0.1 6667
PASS irc
USER <name> 0 * :<realname>
NICK <nick>
```
And you will be registered! Now you have access to the other commands. 

#### HexChat
First, add a network by clicking on "Add", type the name and hit enter:  
<img src="assets/network-list-before.png" alt="network list before" width="400"/>  
Now click "Edit" and enter `localhost/6667` and hit enter.  
Toggle the same checkboxes as shown on the picture and type `irc` in the password field and then click "Close".  
<img src="assets/network-edit.png" alt="network edit" width="400"/>  
Lastly, click "Connect":    
<img src="assets/network-list-after.png" alt="network list after" width="400"/>  
And voila!  
<img src="assets/connected.png" alt="connected" width="400"/>  


## Resources

- [RFC 1459](https://www.rfc-editor.org/info/rfc1459/)
- [RFC 2811](https://www.rfc-editor.org/info/rfc2811/)
- [RFC 2812](https://www.rfc-editor.org/info/rfc2812/)
- [Modern IRC Docs](https://modern.ircdocs.horse/)
- [Claude](https://claude.ai/) and [Gemini](https://gemini.google.com/app) for teaching purposes, debugging and mainly to lift the veil on the complexity of the reglementations and inner workings of the IRC protocol.


