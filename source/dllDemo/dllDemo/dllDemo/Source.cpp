#include <iostream>
#include <Windows.h>
#include <string>
#include <cstring>

//disables error from using depracated function: strcpy()
#pragma warning(disable : 4996)


//function pointer declarations
typedef int(__cdecl * f_ptr)(std::string, int, int);
typedef int(__cdecl * f_ptr2)();

int main()
{
	//used to set search directory for DLLs
	//change this to your own local DLL folder
	//************************************************************************************************************
	bool dllDir = SetDllDirectory(TEXT("C:\\Temp\\GitRepos\\cse687-group1\\source\\TestObjects\\testDLL\\Debug"));
	//************************************************************************************************************


	if (!dllDir)
	{
		std::cout << "directory not found" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "dll directory set" << std::endl;
	}

	std::string test;
	std::cout << "Enter DLL name: "; //enter testDLL.dll for sample dll
	std::cin >> test;
	char* cstr = new char[test.length() + 1];
	std::strcpy(cstr, test.c_str());

	//used to create handler for dll
	HMODULE hGetMod = LoadLibraryA(cstr);


	if (!hGetMod)
	{
		std::cout << "file load fail" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "file load success" << std::endl;
	}

	//assign function pointer to function from DLL
	f_ptr cre_equip = (f_ptr)GetProcAddress(hGetMod, "create_equipment");

	if (!cre_equip)
	{
		std::cout << "function load fail" << std::endl;
	}
	else
	{
		std::cout << "function load success" << std::endl;
	}

	cre_equip("shield", 10, 15);

	std::cout << "shield created with durability: 10  defense: 15" << std::endl;

	f_ptr2 getprop = (f_ptr2)GetProcAddress(hGetMod, "get_equipment_property");

	if (!getprop)
	{
		std::cout << "function load fail" << std::endl;
	}
	else
	{
		std::cout << "function load success" << std::endl;
	}

	std::cout << "defense is: " << getprop();

	std::cout << std::endl << std::endl;

	FreeLibrary(hGetMod);

	if (hGetMod)
	{
		std::cout << "library freed successfully" << std::endl;
	}
	else
	{
		std::cout << "library free failure" << std::endl;
	}

	return EXIT_SUCCESS;


}