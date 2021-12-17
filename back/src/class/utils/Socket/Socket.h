#ifndef DEF_SOCKET
#define DEF_SOCKET

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

class Socket
{
    private:
        // Attributes
        int port, option = 1, listenfd = 0;
        std::string ip;
        struct sockaddr_in serv_addr;

        // Methods
        void init();
        void bind();

    public:
        // Attributes
        int connfd = 0;
        static const int BUFFER_SZ = 2048;
        struct sockaddr_in cli_addr;
        
        // Methods
        void listen();
        void accept(socklen_t);
        void close();
        void close(int);
        
        // Constructor & Destructor
        Socket(std::string, int);
        ~Socket();
};

#endif
