#pragma once

#ifdef VEHICLE_EXPORTS
#define VEHICLE_API __declspec(dllexport)
#else
#define VEHICLE_API __declspec(dllimport)
#endif

#include "../../../TestHarness/TestResult.h"
#include "../../../TestHarness/TestResponse.h"
#include <string>
using std::string;

extern "C" VEHICLE_API void create_vehicle(const string a, const int b, const int c, const int d, const int e);

extern "C" VEHICLE_API void move_vehicle(const int a, const int b);

extern "C" VEHICLE_API void accelerate_vehicle(const int a, const int b);

extern "C" VEHICLE_API void decelerate_vehicle(const int a, const int b);

extern "C" VEHICLE_API int get_vehicle_xpos();

extern "C" VEHICLE_API int get_vehicle_ypos();

extern "C" VEHICLE_API void update_vehicle_pos(const int a);

extern "C" VEHICLE_API TestResponse test();
