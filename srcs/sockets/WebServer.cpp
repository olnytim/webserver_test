#include "../../includes/sockets/WebServer.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

void WebServer::onClientConnected(int client) {
    (void)client;
}

void WebServer::onClientDisconnected(int client) {
    (void)client;
}

void WebServer::onMessageReceived(int client, const char* msg, int length) {
    (void)length;
    std::cout << "hi there" << std::endl;
    std::istringstream iss(msg);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
<<<<<<< HEAD

    std::string content;
    int error_code = 404;

    if (tokens.size() >= 3 && tokens[0] == "GET") {
        std::string filePath = "www/" + tokens[1];
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::ostringstream buffer;
            buffer << file.rdbuf();
            content = buffer.str();
            file.close();
            error_code = 200;
        }
    }
    std::ostringstream response;
    response << "HTTP/1.1 " << error_code << " OK\r\n";
    if (error_code == 200) {
        response << "Content-Type: text/html\r\n"
        << "Content-Length: " << content.size() << "\r\n";
    }
    response << "Connection: close\r\n"
    << "\r\n";
    if (error_code == 200)
        response << content;
    else
        response << "<h1>404 not found</h1>";
=======
    std::string content = "<h1>404 not found</h1>";
    std::string fileHtml = "index.html";
    std::string contentType;
    int error_code = 404;

    if (tokens.size() >= 3 && tokens[0] == "GET") {
        fileHtml = "../www/" + tokens[1];
    }
    std::ifstream f(fileHtml.c_str());
    if (f.good()) {
        error_code = 200;
        std::stringstream buffer;
        buffer << f.rdbuf();
        content = buffer.str();
    }
    if (fileHtml.find(".html") != std::string::npos) {
        contentType = "html";
    } else if (fileHtml.find(".css") != std::string::npos) {
        contentType = "css";
    } else if (fileHtml.find(".jpeg") != std::string::npos) {
        contentType = "jpeg";
        std::fstream f(fileHtml.c_str(), std::ios::in | std::ios::binary);
        if (f.good()) {
            f.seekg(0, std::ios::end);
            content.resize(f.tellg());
            f.seekg(0, std::ios::beg);
            f.read(&content[0], content.size());
        }
    }
    f.close();
    std::ostringstream response;
    std::cout << content.size() << std::endl;
    response << "HTTP/1.1 " << error_code << " OK\r\n"
             << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
             << "Content-Type: text/" << contentType << "\r\n"
             << "Content-Length: " << content.size() << "\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << content;
>>>>>>> 3263dd29320be6e2c8fa7a863d0da9a51488c1d2
    std::string output = response.str();
    std::cout << client << std::endl;
    sendToClient(client, output.c_str(), output.length());
}

//#include "../../includes/sockets/WebServer.hpp"
//#include <fstream>
//#include <vector>
//#include <string>
//#include <iostream>
//#include <sstream>
//
//void WebServer::onClientConnected(int client) {
//    (void)client;
//}
//
//void WebServer::onClientDisconnected(int client) {
//    (void)client;
//}
//
//void WebServer::onMessageReceived(int client, const char* msg, int length) {
//    (void)length;
//    std::istringstream iss(msg);
//    std::vector<std::string> tokens;
//    std::string token;
//    while (std::getline(iss, token, ' ')) {
//        tokens.push_back(token);
//    }
//
//    std::string content = "<h1>404 not found</h1>";
//    std::string fileHtml = "index.html";
//    std::string contentType;
//    int error_code = 404;
//
//    if (tokens.size() >= 3 && tokens[0] == "GET") {
//        fileHtml = "www/" + tokens[1];
//    }
//
//    std::ifstream f(fileHtml.c_str());
//    if (f.good()) {
//        error_code = 200;
//        std::stringstream buffer;
//        buffer << f.rdbuf();
//        content = buffer.str();
//    }
//    if (fileHtml.find(".html") != std::string::npos) {
//        contentType = "html";
//    } else if (fileHtml.find(".css") != std::string::npos) {
//        contentType = "css";
//    } else if (fileHtml.find(".jpeg") != std::string::npos) {
//        contentType = "jpeg";
//        std::fstream f(fileHtml.c_str(), std::ios::in | std::ios::binary);
//        if (f.good()) {
//            f.seekg(0, std::ios::end);
//            content.resize(f.tellg());
//            f.seekg(0, std::ios::beg);
//            f.read(&content[0], content.size());
//        }
//    }
//    f.close();
//    std::ostringstream response;
//    std::cout << content.size() << std::endl;
//    response << "HTTP/1.1 " << error_code << " OK\r\n"
//             << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
//             << "Content-Type: text/" << contentType << "\r\n"
//             << "Content-Length: " << content.size() << "\r\n"
//             << "Connection: close\r\n"
//             << "\r\n"
//             << content;
//    std::string output = response.str();
//    sendToClient(client, output.c_str(), output.length() + 1);
//}
