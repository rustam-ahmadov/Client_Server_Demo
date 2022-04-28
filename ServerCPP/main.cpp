#include"Server.h"
#include"nlohmann/json.hpp"

#include<iostream>
#include <ws2tcpip.h>

//#include"Person.h"

int main() {

	
	SOCKET accept_socket;

	Server server;

	server.SetSocketTcp();
	server.BindSocket();
	server.Listen();



	while ((accept_socket = server.Accept()) != -1) {
		server.Receive(accept_socket);
	}


	

	return 0;
}
