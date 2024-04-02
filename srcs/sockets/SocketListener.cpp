#include "../../includes/sockets/SocketListener.hpp"

bool SocketListener::init() {
    // Initialze winsock (windows)
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
        return true;

    // Create a socket same in windows and linux
    sockets = socket(AF_INET, SOCK_STREAM, 0);
    if (sockets == -1)
        return false;

    // Bind the ip address and port to a socket
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr_in.sin_addr);
    if (bind(sockets, (struct sockaddr*)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) // linux needs to check for -1 instead of SOCKET_ERROR
        return false;

    if (listen(sockets, SOMAXCONN) == SOCKET_ERROR) // linux needs to check for -1 instead of SOCKET_ERROR
        return false;

    // Add the listening socket to the master file descriptor set
    FD_ZERO(&master);
    FD_SET(sockets, &master);

    return true;
}

bool SocketListener::run() {
    while (true) {
        fd_set copy = master;
        int socketCount = select(0, &copy, NULL, NULL, NULL);

        for (int i = 0; i < socketCount; i++)
        {
            int sock = copy.fd_array[i];
            if (sock == sockets) {
                int client = accept(sockets, NULL, NULL);
                FD_SET(client, &master);
                onClientConnected(client);
            }
            else {
                char buf[4096];
                ZeroMemory(buf, 4096);

                // Receive message
                int bytesIn = recv(sock, buf, 4096, 0);
                if (bytesIn <= 0) {
                    // Drop the client
                    onClientDisconnected(sock);
                    closesocket(sock);
                    FD_CLR(sock, &master);
                }
                else {
                    onMessageReceived(sock, buf, bytesIn);
//                    // Check to see if it's a command. \quit kills the server
//                    if (buf[0] == '\\')
//                    {
//                        // Is the command quit?
//                        string cmd = string(buf, bytesIn);
//                        if (cmd == "\\quit")
//                        {
//                            running = false;
//                            break;
//                        }
//
//                        // Unknown command
//                        continue;
//                    }

                    // Send message to other clients, and definiately NOT the listening socket

//                    for (int i = 0; i < master.fd_count; i++)
//                    {
//                        SOCKET outSock = master.fd_array[i];
//                        if (outSock != sockets && outSock != sock)
//                        {
////                            ostringstream ss;
////                            ss << "SOCKET #" << sock << ": " << buf << "\r\n";
////                            string strOut = ss.str();
////
////                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
//                        }
//                    }
                }
            }
        }
    }

    // Remove the listening socket from the master file descriptor set and close it
    // to prevent anyone else trying to connect.
    FD_CLR(sockets, &master);
    closesocket(sockets);

//    // Message to let users know what's happening.
//    string msg = "Server is shutting down. Goodbye\r\n";

    while (master.fd_count > 0)
    {
        // Get the socket number
        SOCKET sock = master.fd_array[0];

//        // Send the goodbye message
//        send(sock, msg.c_str(), msg.size() + 1, 0);

        // Remove it from the master file list and close the socket
        FD_CLR(sock, &master);
        closesocket(sock);
    }

    // Cleanup winsock
    WSACleanup();
    return true;
}

// send and broadcast messages
void SocketListener::sendToClient(int client, const char* msg, int length) {
    send(client, msg, length, 0);
}

void SocketListener::broadcastToClients(int sendingClient, const char* msg, int length) {
    for (int i = 0; i < master.fd_count; i++) {
        int outSock = master.fd_array[i];
        if (outSock != sockets && outSock != sendingClient)
            sendToClient(outSock, msg, length);
    }
}
