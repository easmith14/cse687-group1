/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include "TestProfileLibrary.h"
#include "UserPrompter.h"
#include "CelestialBody.h"
#include "Spacecraft.h"
#include "GaseousCloud.h"
#include <Windows.h>
#include <tchar.h>
#include <experimental/filesystem>

namespace ns = std::experimental::filesystem;

using std::cout;
using std::cin;

//constructor
TestProfileLibrary::TestProfileLibrary()
{
    //cout << "TestProfileLibrary created\n";
}

//destructor
TestProfileLibrary::~TestProfileLibrary()
{
}


//TODO: change this to grab the names of the available dlls and return a vector<string>
vector<string> get_filenames(std::experimental::filesystem::path path)
{
    namespace stdfs = std::experimental::filesystem;

    std::vector<std::string> filenames;

    // http://en.cppreference.com/w/cpp/experimental/fs/directory_iterator
    const stdfs::directory_iterator end{};

    for (stdfs::directory_iterator iter{ path }; iter != end; ++iter)
    {
        // http://en.cppreference.com/w/cpp/experimental/fs/is_regular_file 
        if (stdfs::is_regular_file(*iter))
        {
            if (iter->path().extension().string() == ".dll")
            {
                filenames.push_back(iter->path().filename().string());
            }
        }
    }

    return filenames;
}


//instantiates objects and returns vector of created objects
vector<string> TestProfileLibrary::GetTestList()
{
    const char* relPath = "..\\DLLs";

    char buf[200];
    string path = _fullpath(buf, relPath, 200);
        
    return get_filenames(path);
}

