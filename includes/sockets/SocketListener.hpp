#pragma once

// windows implementation
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

// linux implementation
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <unistd.h>

class SocketListener
{
public:
    bool init();
    bool run();

    SocketListener(unsigned short port, const char* ip) : port(port), ip(ip), sockets(-1), addr_in(), master() {}

protected:
    // handle the events
    virtual void onClientConnected(int client) = 0;
    virtual void onMessageReceived(int client, const char* msg, int length) = 0;
    virtual void onClientDisconnected(int client) = 0;

    // send and broadcast messages
    static void sendToClient(int client, const char* msg, int length);
    void broadcastToClients(int sendingClient, const char* msg, int length);

// windows
private:
    unsigned short  port;
    const char      *ip;
    int             sockets;
    sockaddr_in     addr_in;
    fd_set          master;

// linux
//private:
//    unsigned short    port;
//    const char        *ip;
//    int               sockets;
//    sockaddr_in       addr_in;
//    fd_set            master;
};