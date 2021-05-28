//TCP Client header file

#pragma once

//must include "Ws2_32.lib"
#pragma comment(lib, "Ws2_32.lib")

//must define before #include <WinSock2.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Standard header files
#include <sdkddkver.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <iostream>
#include <string>

#define SCK_VERSION2 0x0202