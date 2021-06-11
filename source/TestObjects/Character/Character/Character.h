#pragma once

#ifdef CHARACTER_EXPORTS
#define CHARACTER_API __declspec(dllexport)
#else
#define CHARACTER_API __declspec(dllimport)
#endif

#include <string>
using std::string;

extern "C" CHARACTER_API void create_character(const string a, const int b);

extern "C" CHARACTER_API void receive_damage(const int a);

extern "C" CHARACTER_API void heal_damage(const int a);

extern "C" CHARACTER_API bool check_if_alive();

extern "C" CHARACTER_API void level_up();
