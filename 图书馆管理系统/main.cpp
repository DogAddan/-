#include "socket.h"
#include "client.h"
#include "server.h"

//#define SERVER
//#define CLIENT
Server* server;

int main()
{

#ifdef CLIENT
    Client client(3009,"127.0.0.1");
    client.start();
#endif

#ifdef SERVER
    server = new Server(3009,"127.0.0.1");
    server->start();
#endif
}
