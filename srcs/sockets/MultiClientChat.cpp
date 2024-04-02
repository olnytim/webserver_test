#include "../../includes/sockets/MultiClientChat.hpp"
#include <string>

void MultiClientChat::onClientConnected(int client) {
    std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
    sendToClient(client, welcomeMsg.c_str(), welcomeMsg.length() + 1);
}

void MultiClientChat::onClientDisconnected(int client)
{

}

void MultiClientChat::onMessageReceived(int client, const char* msg, int length) {
    broadcastToClients(client, msg, length);
}
