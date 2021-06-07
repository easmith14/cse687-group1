//TCP CLIENT source

#include "client.h"
#include "JsonMessageGenerator.h"
#include "json.h"
#include <string>
#include <vector>
#include <functional>
#include <exception>
#include <thread>

#define DEFAULT_PORT "13379"

using std::cout;
using std::cin;

vector<string> split(string text, string delimiter)
{
	vector<string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = text.find(delimiter)) != std::string::npos)
	{
		token = text.substr(0, pos);
		tokens.push_back(token);
		text.erase(0, pos + delimiter.length());
	}
	if (text != "")
	{
		tokens.push_back(text);
	}

	return tokens;
}

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
	const int recvbuflen = 1024;
	const char* sendbuf = "client is ready\n";
	const char* msg_exit = "\nserver connection closing...\n\n";
	char recvbuf1[recvbuflen] = { 0 };
	char recvbuf2[recvbuflen] = { 0 };
	string recvdmsg;
	JsonMessageGenerator jsonMessageGenerator("Client", result->ai_addr->sa_data, "stand-in destination addr");
	
	// Connect to server.
	cout << "\n\tConnecting to server...  ";
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// recieve welcome and class list from server
	iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
	if (iResult > 0)
		cout << "server connection established\n\n";
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());
	Json::Value welcomeMessage = jsonMessageGenerator.GetValueFromJsonString(recvbuf1);

	recvbuf1[0] = '\0';// clear receive buffer
	iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
	if (iResult > 0)
		cout << "server connection established\n\n";
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());
	Json::Value options = jsonMessageGenerator.GetValueFromJsonString(recvbuf1);

	//print the greetings to the screen
	cout << welcomeMessage["Body"].asString() << jsonMessageGenerator.GetStringFromClassesJson(options);


	// run client cmd interface
	bool keepGoing = true;
	string usrInput;
	std::vector<std::thread> threads;

	while (keepGoing)
	{
		int expectedResponses = 1;
		cin >> usrInput;

		//if a flagged command, send it
		if (usrInput.substr(0, 2) == "--")
		{
			cout << "sending command-";
			const char* message = jsonMessageGenerator.GenerateMessage(usrInput, JsonMessageGenerator::MessageType::UserCommand);
			iResult = send(ConnectSocket, message, (int)strlen(message), 0);
			cout << "sent-";
		}
		else
		{
			//we split the potential classes selected by spaces, then parse the single values if possible, else leave them
			vector<string> arguments = split(usrInput, ",");

			//we expect an acknowledgement and a result for each valid request

			expectedResponses = 2*arguments.size();

			for (string argument : arguments)
			{
				try
				{
					//verify argument is both an integer and within our range
					int choiceIndex = std::stoi(argument);
					int t = options["Body"].size();
					if (choiceIndex < 1 || choiceIndex > options["Body"].size())
					{
						throw std::exception();
					}

					//grab the appropriate class name and send it
					string choiceString = options["Body"][choiceIndex - 1].asString();
					const char* message = jsonMessageGenerator.GenerateMessage(choiceString, JsonMessageGenerator::MessageType::ClassSelection);
					iResult = send(ConnectSocket, message, (int)strlen(message), 0);
				}
				catch(std::exception e)
				{
					//send the known bad message to get error handling from server.
					//decrement expected responses
					const char* message = jsonMessageGenerator.GenerateMessage(argument, JsonMessageGenerator::MessageType::Error);
					iResult = send(ConnectSocket, message, (int)strlen(message), 0);
					expectedResponses--;
				}
			}
			//iResult = shutdown(ConnectSocket, SD_SEND);
		}

		iResult = shutdown(ConnectSocket, SD_SEND);

		do { 
			recvbuf1[0] = '\0';// clear receive buffer
			cout << "receiving-";
			iResult = recv(ConnectSocket, recvbuf1, recvbuflen, 0);
			cout << "received\n";
			recvdmsg = recvbuf1;
			Json::Value val = jsonMessageGenerator.GetValueFromJsonString(recvdmsg);

			if (val["MessageType"].asInt() == JsonMessageGenerator::MessageType::ClassOptions)
			{
				cout << jsonMessageGenerator.GetStringFromClassesJson(val);
			}

			if (val["MessageType"].asInt() == JsonMessageGenerator::MessageType::TestResult)
			{
				//TODO: might want some other formatting logic in the json class here
				cout << "\n" << val["Body"] << "\n>";
			}

			else if (val["MessageType"].asInt() == JsonMessageGenerator::MessageType::Exit)
			{
				iResult = 0;
			}

			else
			{
				cout << val["Body"].asString();
			}

			cout << "received: " << expectedResponses << "\n";
			expectedResponses--;

			if (expectedResponses == 0)
			{
				iResult = 0;
			}

		} while (iResult > 0);
	}

		shutdown(ConnectSocket,SD_BOTH);
	

	system("PAUSE");
	exit(1);
}