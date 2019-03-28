#include "socket.h"

Socket::Socket(u_int16_t port, const char* ipAddr) : port(port)
{
    this->ipAddr = new char[strlen(ipAddr)+1];
    strcpy(this->ipAddr,ipAddr);

    addr = new sockaddr_in[sizeof(sockaddr_in)];
}

Socket::~Socket(void)
{
	close(sockFd);
	delete ipAddr;
	delete addr;
}

void Socket::createSocket()
{
    sockFd = socket(AF_INET,SOCK_STREAM,0);
    if(sockFd < 0)
    {
        throw "socket 创建失败!";
    }
}

void Socket::initSocket()
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = inet_addr(ipAddr);
}

void Socket::connectSocket()
{
    if(connect(sockFd,(sockaddr*)addr,sizeof(*addr)) < 0)
    {
        throw "连接失败！";
    }
}

void Socket::bindSocket(void)
{
    len = sizeof(*addr);
    if(bind(sockFd,(sockaddr*)addr,len) < 0)
    {
        throw "绑定失败！";
    }
}

void Socket::listenSocket(int num)
{
    listen(sockFd,num);
}

int Socket::acceptSocket(void)
{
    struct sockaddr_in from_addr;
    int acceptFd = accept(sockFd,(sockaddr*)&from_addr,&len);
    if(acceptFd < 0)
    {
        throw "创建连接对象失败！";
    }
    return acceptFd;

}
