#include "../../includes/sockets/WebServer.hpp"
#include <string>

void WebServer::onClientConnected(int client) {
}

void WebServer::onClientDisconnected(int client) {
}

void WebServer::onMessageReceived(int client, const char* msg, int length) {
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n"
             << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
             << "Content-Type: text/html\r\n"
             << "Content-Length: 11\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << "Hello World";
    sendToClient(client, response.str().c_str(), response.str().length() + 1);
}