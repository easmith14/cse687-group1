//TCP CLIENT source

#include "client.h"

using namespace std;

void main()
{
	//client locals
	long successful;
	WSAData winSockData;
	WORD dllversion;

	dllversion = MAKEWORD(2, 1);  //set dllversion
	successful = WSAStartup(dllversion, &winSockData); //fire up winsock

	string response;
	string converter;
	char message[200];

	SOCKADDR_IN address;

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, NULL);

	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_family = AF_INET;
	address.sin_port = htons(444);

	cout << "\n\tCLIENT: Do you want to connect to the server?  (Y/N)";
	cin >> response;

	response[0] = tolower(response[0]);

	if (response == "n")
	{
		cout << "\n\tQuitting";
	}
	else if (response == "y")
	{
		connect(sock, (SOCKADDR*)&address, sizeof(address));

		successful = recv(sock, message, sizeof(message), NULL);

		converter = message;

		cout << "\n\tMessage from SERVER:\n\n\t" << converter << endl;
	}
	else
	{
		cout << "\n\nInvalid entry";
	}

	cout << "\n\n\t";
	system("PAUSE");
	exit(1);

}