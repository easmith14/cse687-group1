//TCP CLIENT source

#include "client.h"
#include "JsonMessageGenerator.h"
#include "json.h"
#include <string>

using namespace std;
#define DEFAULT_PORT "1337"

int main()
{
	//client locals
	long SUCCESSFUL;
	WSADATA wsaData;
	WORD DLLVERSION;

	//Create WORD value to set version 22
	DLLVERSION = MAKEWORD(2, 2);

	//Start WinSock DLL
	SUCCESSFUL = WSAStartup(DLLVERSION, &wsaData);

	struct addrinfo* result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);

	SOCKET ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to the first address returned by the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
	}

	//ready to connect
	cout << "\n\tCLIENT: Ready to connect - ";
	system("PAUSE");

	//prep buffer and client messages
	int recvbuflen = 512;
	const char* sendbuf = "client is ready\n";
	const char* msg_exit = "\nserver connection closing...\n\n";
	char recvbuf1[512] = { 0 };
	char recvbuf2[512] = { 0 };
	string recvdmsg;

	//int iResult;
	
	// Connect to server.
	cout << "\n\tConnecting to server...  ";
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// recieve welcome from server
	iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
	std::string msg1 = recvbuf1;
	if (iResult > 0)
		cout << "server connection establish\n\n" << msg1;
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());



	// run client cmd interface
	bool keepGoing = true;
	string usrInput;
	char* usrInputCh;
	JsonMessageGenerator jsonMessageGenerator("Client", result->ai_addr->sa_data, "stand-in destination addr");


	while (keepGoing)
	{
		//cout << "start loop";
		cin >> usrInput;
		cout << "sending-";
		const char* message = jsonMessageGenerator.GenerateMessage(usrInput, JsonMessageGenerator::MessageType::ClassSelection);
		iResult = send(ConnectSocket, message, (int)strlen(message), 0);
		cout << "sent-";
		
		memset(recvbuf1, 0, sizeof(recvbuf1));
		cout << "receiving-";
		iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
		cout << "received";
		recvdmsg = recvbuf1;
		Json::Value val = jsonMessageGenerator.GetValueFromJsonString(recvdmsg);

		//recieve as many responses as we sent in a loop
		if (val["MessageType"] == std::to_string((int)JsonMessageGenerator::MessageType::ClassOptions))
		{
			Json::Value classes = val["Body"];
			//for
		}

		else if (val["MessageType"] == std::to_string((int)JsonMessageGenerator::MessageType::Exit))
		{
			keepGoing = false;
		}

		else
		{
			cout << val["Body"];
		}
	}
	
	iResult = shutdown(ConnectSocket, SD_SEND);

	system("PAUSE");
	exit(1);
}