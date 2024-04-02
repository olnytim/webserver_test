#include "../../includes/sockets/WebServer.hpp"
#include <fstream>

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

//#include "../../includes/sockets/WebServer.hpp"
//#include <fstream>
//
//void WebServer::onClientConnected(int client) {
//}
//
//void WebServer::onClientDisconnected(int client) {
//}
//
//void WebServer::onMessageReceived(int client, const char* msg, int length) {
//    std::ifstream f("../../www/index.html");
//    std::string output = "404 not found";
//    if (f.good()) {
//        std::ostringstream response;
//        response << "HTTP/1.1 200 OK\r\n"
//                 << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
//                 << "Content-Type: text/html\r\n"
//                 << "Content-Length: 11\r\n"
//                 << "Connection: close\r\n"
//                 << "\r\n"
//                 << "Hello World";
//        output = response.str();
//    }
//    sendToClient(client, output.c_str(), output.length() + 1);
//}
