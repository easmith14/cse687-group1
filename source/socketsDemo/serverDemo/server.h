//TCP Server header file

#pragma once
//following adds "Ws2_32.lib" to the linker
#pragma comment (lib, "Ws2_32.lib")

//STD console headers
#include <sdkddkver.h>
#include <conio.h>
#include <stdio.h>

//must define before #include <WinSock2.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//SOCKET headers
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

//WinSock version 2
#define SCK_VERSION2 0x0202

