#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include "Monster.h"
#include <vector>


class  monsterManager
{
public:
	monsterManager();
	~monsterManager();

	enum MONSTER_TYPE{
		T_ENEMYPROBE = 0,
		T_ENEMYBEHOLDER,
		T_NUMTYPE
	};

	void initRandPos(MONSTER_TYPE monsterType, int maxMonster, Vector3 playerPos, Vector3 minPos, Vector3 maxPos);
	void add(GameObject*gameobject);
	static std::vector<Vector3>monsterPos;
private:
	int numMonster;
	int randPos;
	int randX, randY, randZ;

};

#endif