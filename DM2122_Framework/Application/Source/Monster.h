#ifndef MONSTER_H
#define MONSTER_H

#include "Characters.h"


class Monster :public Characters
{
public:
	enum MONSTER_TYPE{
		T_ENEMYPROBE,
		T_ENEMYBEHOLDER,
		T_NUMTYPE,
	};
	Monster();
	Monster(Scene*, const string&name, Vector3&position, const int &health);
	Monster(Scene*, const string&name, Vector3&position, const int &health, const int &damage);
	Monster(Scene*, const string&name, Vector3&position, MONSTER_TYPE monster);
	virtual ~Monster();

	virtual void setHealth(int hp);
	virtual int getHealth();
	virtual void setDamage(int att);
	virtual int getDamage();

	virtual bool anyInteraction();
	virtual void render();

private:
	int health;
	int damage;

};

#endif