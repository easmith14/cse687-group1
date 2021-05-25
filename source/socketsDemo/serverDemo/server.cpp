//TCP Server source

#include "server.h"

using namespace std;

void main() 
{
	//server main local
	long SUCCESSFUL;
	WSAData WinSockData;
	WORD DLLVERSION;

	//Create WORD value to set version 21
	DLLVERSION = MAKEWORD(2, 1);

	//Start WinSock DLL
	SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData);

	//Create Socket Structure
	SOCKADDR_IN address;
	int addressSize = sizeof(address);

	//Create Sockets
	SOCKET sock_listen;  //listen for incoming connections
	SOCKET sock_connection; //active if connecitons found

	//Socket arguments 
	// AF_INET = internet domain
	// SOCK_STREAM = connection oriented TCP not SOCK_DGRAM (UDP)
	sock_connection = socket(AF_INET, SOCK_STREAM, NULL);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");  //set IP
	address.sin_family = AF_INET;  //set family
	address.sin_port = htons(444); //set port use htons to conver to network type 

	sock_listen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock_listen, (SOCKADDR*)&address, sizeof(address));
	listen(sock_listen, SOMAXCONN);  //listen without limit

	//if connection found
	for (;;)
	{
		cout << "\n\tSERVER:  Waiting for incoming connection...";

		if (sock_connection = accept(sock_listen, (SOCKADDR*)&address, &addressSize))
		{
			cout << "\n\tA connection was found!" << endl;

			SUCCESSFUL = send(sock_connection, "Welcome!  Server connection established!", 42, NULL);
		}
	}
	
}