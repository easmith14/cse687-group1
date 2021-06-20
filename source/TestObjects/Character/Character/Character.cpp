#include <string>
#include "pch.h"
#include "Character.h"
#include "../../../TestHarness/TestResponse.h"
#include "../../../TestHarness/TestResult.h"
using std::string;

static string _CharName;
static int _CharLevel;
static int _CharMaxHealth;
static int _CharCurrentHealth;
static int _CharStrength;
static int _CharDexterity;
static int _CharIntelligence;

static const int _HealthBase = 100;
static const int _HealthScalingFactor = 10;
static const int _StatBase = 5;
static const int _StatScalingFactor = 1;

void create_character(const string a, const int b)
{
	_CharName = a;
	_CharLevel = b;

	// Stats determined by base amount plus scaling amount per level
	// stat = base + scaling_factor * level
	_CharMaxHealth = _HealthBase + _HealthScalingFactor * _CharLevel;
	_CharStrength = _StatBase + _StatScalingFactor * _CharLevel;
	_CharDexterity = _StatBase + _StatScalingFactor * _CharLevel;
	_CharIntelligence = _StatBase + _StatScalingFactor * _CharLevel;

	// Set current health to max health for new character
	_CharCurrentHealth = _CharMaxHealth;

}

void receive_damage(const int a)
{
	_CharCurrentHealth = _CharCurrentHealth - a;
	
	if (_CharCurrentHealth < 0)
	{
		_CharCurrentHealth = 0;
	}
}

void heal_damage(const int a)
{
	_CharCurrentHealth = _CharCurrentHealth + a;

	if (_CharCurrentHealth > _CharMaxHealth)
	{
		_CharCurrentHealth = _CharMaxHealth;
	}
}

bool check_if_alive()
{
	if (_CharCurrentHealth <= 0)
	{
		return false;
	}

	return true;
}

void level_up()
{
	_CharMaxHealth = _CharMaxHealth + _HealthScalingFactor;
	_CharStrength = _CharStrength + _StatScalingFactor;
	_CharDexterity = _CharDexterity + _StatScalingFactor;
	_CharIntelligence = _CharIntelligence + _StatScalingFactor;

	// increase current health by same amount
	_CharCurrentHealth = _CharCurrentHealth + _HealthScalingFactor;
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

	// Test Case 2 : Level Up Check
	TestResult levelUpResult;
	levelUpResult.LogLevel = 1;
	levelUpResult.TestName = "Level Up Check";
	levelUpResult.TestNotes = "Check whether or not the level-up system is working";
	levelUpResult.TestNumber = 2;
	int origStrength = _CharStrength;
	level_up();
	if (origStrength == _CharStrength + 1)
	{
		levelUpResult.TestSuccess = true;
	}
	else
	{
		levelUpResult.TestSuccess = false;
	}
	response.Results.push_back(levelUpResult);

	// Test Case 3 : Character Transcends Humanity
	TestResult transcendResult;
	transcendResult.LogLevel = 1;
	transcendResult.TestName = "Transcend Mortal Coil";
	transcendResult.TestNotes = "And this is to go even further.. beyond";
	transcendResult.TestNumber = 3;

	int thresholdOfGreatness = 1000;
	for (int i = 0; i < thresholdOfGreatness; i++)
	{
		level_up();
	}
	// if the test made it this far then it is a pass
	transcendResult.TestSuccess = true;
	response.Results.push_back(transcendResult);

	return response;

}