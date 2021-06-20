#pragma once

#ifdef CHARACTER_EXPORTS
#define CHARACTER_API __declspec(dllexport)
#else
#define CHARACTER_API __declspec(dllimport)
#endif

#include "../../../TestHarness/TestResult.h"
#include "../../../TestHarness/TestResponse.h"
#include <string>
using std::string;

extern "C" CHARACTER_API void create_entity(const string a, const int b, const int c, const int d, const int e);

extern "C" CHARACTER_API void receive_damage(const int a);

extern "C" CHARACTER_API void heal_damage(const int a);

extern "C" CHARACTER_API bool check_if_alive();

extern "C" CHARACTER_API void level_up();

extern "C" CHARACTER_API TestResponse test();
