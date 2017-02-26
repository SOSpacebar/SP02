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

	enum AI_STATE {

		AI_IDLE = 0,
		AI_CHASE,
		AI_ATTACK

	};

	Monster();
	Monster(Scene*, const string&name, Vector3&position, const int &health);
	Monster(Scene*, const string&name, Vector3&position, const int &health, const int &damage);
	Monster(Scene*, const string&name, Vector3&position, MONSTER_TYPE monster);
	virtual ~Monster();

	virtual void setDamage(int att);
	virtual int getDamage();

	virtual bool anyInteraction();
	virtual void render();
private:
	int damage;

	float attackInterval = 0.25f;
	float attackTimer = 0;

	float attackDistance = 0;

	AI_STATE currentState = AI_IDLE;

	float speed = 0;
	float acceleration_ = 0;
	float maxSpeed = 0;

	float timer;

	Vector3* nearestMonsterPos;

};

#endif