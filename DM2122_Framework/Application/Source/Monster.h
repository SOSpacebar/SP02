#define MONSTER_H
#ifndef MONSTER_H
#endif

#include "Characters.h"


class Monster :public Characters
{
public:
	Monster();
	Monster(const string&name, Vector3&position, const int &health);
	Monster(const string&name, Vector3&position, const int &health, const int &damage);
	virtual ~Monster();

	virtual void setHealth(int hp);
	virtual int getHealth();
	virtual void setDamage(int att);
	virtual int getDamage();
	//virtual void setMonsterName(string name);
	//string getMonsterName();

private:
	int health;
	int damage;
	//string monsterName;

};
