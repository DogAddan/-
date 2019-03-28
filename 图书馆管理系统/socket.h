#ifndef SOCKET_H
#define SOCKET_H

#include "struct.h"
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

class Socket
{
    int sockFd;
    u_int16_t port;
    char* ipAddr;
    sockaddr_in* addr;
    socklen_t len;

public:
    Socket(u_int16_t port,const char* ipAddr);
	~Socket(void);
    //创建socket对象
    void createSocket(void);
    //准备通信地址
    void initSocket(void);
    //连接
    void connectSocket(void);
    //绑定
    void bindSocket(void);
    //监听
    void listenSocket(int num);
    //
    int acceptSocket(void);
    //发送
    template <typename T> void msgSend(int acceptFd,const T& buf)
    {
        send(acceptFd,buf, sizeof(T),0);
    }
    template <typename T> void msgSend(const T* buf)
    {
        send(sockFd,buf, sizeof(T),0);
    }
    //接收
    template <typename T> void msgRecv(T& buf)
    {
        if(recv(sockFd,buf,sizeof(T),0) <= 0)
        {
            throw "收到错误消息!";
        }
    }
    template <typename T> void msgRecv(int acceptFd,T* buf)
    {
        if(recv(acceptFd,buf,sizeof(T),0) <= 0)
        {
            throw "收到错误消息!";
        }
    }
};

#endif //SOCKET_H
