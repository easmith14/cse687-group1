//TCP CLIENT source

#include "client.h"
#include <string>

using namespace std;
#define DEFAULT_PORT "444"

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
	std::string response;
	cout << "\n\tCLIENT: Do you want to connect to the server?  (Y/N)";
	cin >> response;

	response[0] = tolower(response[0]);
	if (response == "n")
	{
		cout << "\n\tQuitting";
		exit(1);
	}
	else if (response == "y")
	{
		int recvbuflen = 512;
		const char* sendbuf = "client is ready\n";
		const char* sendtest = "Test Request";
		char recvbuf1[512] = { 0 };
		char recvbuf2[512] = { 0 };

		int iResult;
		// Connect to server.
		cout << "\n\ttrying to connect to server...\n";
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
		}
			// send initial message
			iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
			}
			iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0); // recieve response from server
			std::string msg1 = recvbuf1;
			cout << "message from server: " << msg1 << "\n";
			if (iResult > 0)
				printf("Bytes received: %d\n", iResult);
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed: %d\n", WSAGetLastError());

			// send test request
			iResult = send(ConnectSocket, sendtest, (int)strlen(sendbuf), 0);
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
			iResult = shutdown(ConnectSocket, SD_SEND);
	}
	system("PAUSE");
	exit(1);
}