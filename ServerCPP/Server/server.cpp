#include "server.h"
#include "person.h"

#include<iostream>
#include <ws2tcpip.h>

#include<thread>
#include<vector>

#include"nlohmann/json.hpp"
using json = nlohmann::json;



Server::Server()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed.\n";
		exit(1);
	}
}


void Server::SetSocketTcp()
{
	_protocolType = ProtocolTypes::TCP;
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	_isSocketSet = 1;
}
void Server::SetSocketUdp(int portNumber)
{
	_isSocketSet = 1;
}

int Server::BindSocket()
{
	if (_isSocketSet)
		if (_protocolType == ProtocolTypes::TCP)
		{
			memset(sockaddr_inServer.sin_zero, '\0', sizeof sockaddr_inServer.sin_zero);

			sockaddr_inServer.sin_family = AF_INET;
			sockaddr_inServer.sin_port = htons(PORT);
			inet_pton(AF_INET, "127.0.0.1", &(sockaddr_inServer.sin_addr));

			if (bind(_socket, (sockaddr*)&sockaddr_inServer, sizeof sockaddr_inServer) == -1) {
				std::cerr << "Error,socket couldn't bind";
				return -1;
			}
			return 0;
		}

	std::cerr << "Socket has not been set yet.\n";
	return -1;
}
int Server::Listen()
{
	int isListen = listen(_socket, SOMAXCONN) == false;
	if (isListen) {
		std::cout << "Server listening...\n";
		return isListen;
	}
	std::cout << "Server can't listen";
	return isListen;
}

SOCKET Server::Accept() {

	SOCKET accept_socket;
	struct sockaddr_storage sockadd_ssClient;
	int size = sizeof(sockadd_ssClient);

	if ((accept_socket = accept(_socket, (sockaddr*)&sockadd_ssClient, &size)) != -1) {

		getpeername(accept_socket, (sockaddr*)&sockadd_ssClient, &size);

		if (sockadd_ssClient.ss_family == AF_INET) {

			sockaddr_in* client = (sockaddr_in*)&sockadd_ssClient;
			int clientPort = ntohs(client->sin_port);
			char clientIpAddr[INET6_ADDRSTRLEN];

			//convert network to presentation
			inet_ntop(AF_INET, &client->sin_addr, clientIpAddr, sizeof clientIpAddr);

			std::cout << "Client IP:" << ' ' << clientIpAddr << std::endl;
			std::cout << "Client Port:" << ' ' << clientPort << std::endl;
		}
	}
	return accept_socket;
}

int Server::Receive(SOCKET &socket) {

	int numBytes;
	numBytes = recv(socket, buff, MAXDATASIZE - 1, 0);
	buff[numBytes] = '\0';
	
	char* jsonBuff = new char[numBytes];
	for (int i = 0; i < numBytes; i++)	
		jsonBuff[i] = buff[i];
	

	
	//parse buff to json format without '\  \  \  \' 
	json j = json::parse(buff);

	//json j1 = json{ {"Name", p.Get_Name()},  {"Age", p.Get_Age()} };

	Person p;

	std::string personName = j["Name"].get<std::string>();	
	int personAge;
	j.at("Age").get_to(personAge);
	
	p.Set_Name(personName);
	p.Set_Age(personAge);
	
	p.Set_Age(30);
	p.Set_Name("Mr Rustam");

	json j1 = json{ {"Name", p.Get_Name()},  {"Age", p.Get_Age()} };
	
	std::string s = j1.dump();

	char* c = const_cast<char*>(s.c_str());
	std::cout << c;
	std::cout << "Received information" << std::endl;
	std::cout <<"Person Name -  "<< p.Get_Name() << std::endl;
	std::cout <<"Person Age  -  "<< p.Get_Age() << std::endl;
	

	send(socket,c, sizeof s+1,0);


	

	return numBytes;
}
