#include "../includes/sockets/WebServer.hpp"

int main()
{
    WebServer server(8083, "0.0.0.0");
    if (!server.init())
        return 1;
    server.run();

//    system("pause");
}