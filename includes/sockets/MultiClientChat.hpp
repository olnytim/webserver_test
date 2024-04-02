#pragma once

#include "SocketListener.hpp"

class MultiClientChat : public SocketListener
{
public:
    MultiClientChat(unsigned short port, const char* ip) :
        SocketListener(port, ip) {}

protected:
    void onClientConnected(int client);
    void onMessageReceived(int client, const char* msg, int length);
    void onClientDisconnected(int client);
};