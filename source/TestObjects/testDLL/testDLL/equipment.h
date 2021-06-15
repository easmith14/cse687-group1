#pragma once

#ifdef EQUIPMENT_EXPORTS
#define EQUIPMENT_API __declspec(dllexport)
#else
#define EQUIPMENT_API __declspec(dllimport)
#endif

#include "../../../TestHarness/TestResult.h"
#include "../../../TestHarness/TestResponse.h"
#include <string>

using std::string;

extern "C" EQUIPMENT_API void create_equipment(const string a, const int b, const int c);

extern "C" EQUIPMENT_API void degrade_equipment(const int a);

extern "C" EQUIPMENT_API void repair_equipment(const int a);

extern "C" EQUIPMENT_API void upgrade_equipment(const int a);

extern "C" EQUIPMENT_API void destroy_equipment();

extern "C" EQUIPMENT_API int get_equipment_property();

extern "C" EQUIPMENT_API int get_equipment_durability();

extern "C" EQUIPMENT_API TestResponse test();