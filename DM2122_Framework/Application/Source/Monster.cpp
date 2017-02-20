#include "Monster.h"

Monster::Monster(Scene* scene, const string&name, Vector3&position, const int &health) : Characters(scene, name, position), health(0)
{
}

Monster::Monster(Scene* scene, const string&name, Vector3&position, const int &health, const int &damage) : Characters(scene, name, position), health(0), damage(0)
{
}

Monster::~Monster()
{
}

void Monster::setHealth(int hp)
{
	this->health = hp;
}

int Monster::getHealth()
{
	return this->health;
}

void Monster::setDamage(int att)
{
	this->damage = att;
}

int Monster::getDamage()
{
	return this->damage;
}

//void Monster::setMonsterName(string name)
//{
//	this->monsterName = name;
//}

//string Monster::getMonsterName()
//{
//	return this->monsterName;
//}