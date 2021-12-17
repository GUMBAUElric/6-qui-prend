#include "Socket.h"
#include "Log.h"

using namespace std;

Socket::Socket(std::string ip, int port)
{
    this->ip = ip;
    this->port = port;
    this->init();
}

Socket::~Socket()
{
}

/******************
*     Methods     *
*******************/

void Socket::init() {
    this->listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->connfd == -1) {
        Log::writeError("Socket connection failed");
        return;
    }

    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    this->serv_addr.sin_port = htons(this->port);

    int setsockopt = ::setsockopt(this->listenfd, SOL_SOCKET, SO_REUSEADDR , &this->option, sizeof(this->option));

    if(setsockopt == -1) {
        Log::writeError("Setsockopt failed");
        return;
    }

    this->bind();
}

void Socket::bind() {
    int bind_fd = ::bind(this->listenfd, (struct sockaddr*)&this->serv_addr, sizeof(this->serv_addr));

   if (bind_fd == -1) {
        Log::writeError("Bind socket failed");
        return;
   }
}

void Socket::listen() {
    int listen = ::listen(this->listenfd, 10);

    if (listen == -1) {
         Log::writeError("Listen socket failed");

        return;
    }

    Log::write("SOCKET", "=== SERVER STARTED ===");
}

void Socket::accept(socklen_t clilen) {
    this->connfd = ::accept(this->listenfd, (struct sockaddr*)&this->cli_addr, &clilen);

    Log::write("SOCKET", "Got connection from " + string(inet_ntoa(this->cli_addr.sin_addr)));
}

void Socket::close() {
    ::close(this->connfd);
}

void Socket::close(int connfd) {
    ::close(connfd);
}
