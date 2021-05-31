//TCP CLIENT source

#include "client.h"
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
	const char* sendtest1 = "Test Request1";
	const char* sendtest2 = "Test Request2";
	const char* runtest1 = "runtest1";
	const char* runtest2 = "runtest2";
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

	while (keepGoing)
	{
		//cout << "start loop";
		cin >> usrInput;
		sendbuf = usrInput.c_str();
		cout << "sending-";
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		cout << "sent-";
		
		memset(recvbuf1, 0, sizeof(recvbuf1));
		cout << "receiving-";
		iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
		cout << "received";
		recvdmsg = recvbuf1;
		cout << recvdmsg;
		if (std::strcmp(sendbuf, runtest1) == 0 || std::strcmp(sendbuf, runtest2) == 0)
		{
			memset(recvbuf1, 0, sizeof(recvbuf1));
			iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
			recvdmsg = recvbuf1;
			cout << recvdmsg;
			memset(recvbuf1, 0, sizeof(recvbuf1));
		}

		if (usrInput == "exit")
		{
			keepGoing = false;
		}

	}





	/*
	// send test request1
	iResult = send(ConnectSocket, sendtest1, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
	recvbuf1[0] = '\0'; //clear buffer  
	iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0); // first receive ack
	std::string msg2 = recvbuf1;
	cout << "message from server: " << msg2 << "\n";
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());

	// send test request2
	iResult = send(ConnectSocket, sendtest2, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
	recvbuf1[0] = '\0'; //clear buffer  
	iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0); // first receive ack
	msg2 = recvbuf1;
	cout << "message from server: " << msg2 << "\n";
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());

	iResult = shutdown(ConnectSocket, SD_SEND);

	recvbuf2[0] = '\0'; //clear buffer
	iResult = recv(ConnectSocket, recvbuf2, recvbuflen, 0); // second is test response
	std::string msg3 = recvbuf2;
	cout << "message from server: " << msg3 << "\n";
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());

	recvbuf2[0] = '\0'; //clear buffer
	iResult = recv(ConnectSocket, recvbuf2, recvbuflen, 0); // second is test response
	msg3 = recvbuf2;
	cout << "message from server: " << msg3 << "\n";
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());
	*/
	
	iResult = shutdown(ConnectSocket, SD_SEND);

	system("PAUSE");
	exit(1);
}