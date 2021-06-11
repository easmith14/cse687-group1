#include <string>
#include "pch.h"
#include "Character.h"
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
