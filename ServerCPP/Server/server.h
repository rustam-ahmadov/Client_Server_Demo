#pragma once
#include "winsock2.h"
#pragma comment(lib, "Ws2_32.lib")

#define MAXDATASIZE 100
#define PORT 8080

enum ProtocolTypes
{
    TCP,
    UDP
};

class Server
{
private:
    SOCKET _socket;
    bool _isSocketSet = 0;
    ProtocolTypes _protocolType;
    sockaddr_in sockaddr_inServer;

    char buff[MAXDATASIZE];

public:
    Server();

    void SetSocketTcp();
    void SetSocketUdp(int portNumber);

    int BindSocket();
    int Listen();
    SOCKET Accept();

    int Receive(SOCKET &socket);

};
