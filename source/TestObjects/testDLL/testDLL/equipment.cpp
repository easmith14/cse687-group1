#include "pch.h"
#include "equipment.h"
#include "../../../TestHarness/TestResult.h"
#include "../../../TestHarness/TestResponse.h"
#include <string>

using std::string;
static string _EquipmentName;
static int _durability;
static int _property;
static int _saved_property;


 void create_equipment(const string a, const int b, const int c)
{
	_EquipmentName = a;
	_durability = b;
	_property = c;
	_saved_property = _property;
}

 void degrade_equipment(const int a)
{
	_durability -= a;
	
	if (_durability <= 0)
	{
		destroy_equipment();
	}
}

 void repair_equipment(const int a)
{
	_durability += a;
	_property = _saved_property;
}

 void upgrade_equipment(const int a)
{
	_property += a;
}

 void destroy_equipment()
{
	_property = 0;
}

 int get_equipment_property()
{
	return _property;
}

 TestResponse test()
{
	 TestResponse response;

	 // Test Case 1 : Passing Case
	 TestResult passResult;
	 passResult.LogLevel = 3;
	 passResult.TestName = "PASS Test";
	 passResult.TestNotes = "This test will always pass";
	 passResult.TestNumber = 1;
	 passResult.TestSuccess = true;
	 response.Results.push_back(passResult);

	 // Test Case 2 : Degrade Check
	 TestResult degradeResult;
	 degradeResult.LogLevel = 1;
	 degradeResult.TestName = "Degrade Check";
	 degradeResult.TestNotes = "Check whether or not the degrade system is working";
	 degradeResult.TestNumber = 2;
	 int origDurability = _durability;
	 int changeVal = 1;
	 degrade_equipment(changeVal);
	 if (origDurability == _durability - changeVal)
	 {
		 degradeResult.TestSuccess = true;
	 }
	 else
	 {
		 degradeResult.TestSuccess = false;
	 }
	 response.Results.push_back(degradeResult);

	 //// Test Case 3 : Character Transcends Humanity
	 //TestResult transcendResult;
	 //transcendResult.LogLevel = 1;
	 //transcendResult.TestName = "Transcend Mortal Coil";
	 //transcendResult.TestNotes = "And this is to go even further.. beyond";
	 //transcendResult.TestNumber = 3;

	 //// test should break since level is stored as an int
	 //unsigned long maxULong = 2147483647;
	 //for (unsigned long i = 0; i < maxULong; i++)
	 //{
		// level_up();
	 //}
	 //// if the test made it this far then it is a pass
	 //transcendResult.TestSuccess = true;
	 //response.Results.push_back(transcendResult);

	 return response;

}
