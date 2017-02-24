#include "monsterManager.h"
std::vector<Vector3>monsterManager::monsterPos;

monsterManager::monsterManager()
{
}

monsterManager::~monsterManager()
{
}

void monsterManager::initRandPos(MONSTER_TYPE monsterType, int maxMonster, Vector3 playerPos, Vector3 minPos, Vector3 maxPos)
{
	for (int i = 0; !monsterPos.empty(); i++)
	{
		monsterPos.pop_back();
	}
	if (monsterType == T_ENEMYPROBE)
	{
		srand(time(NULL) + 1);
	}
	if (monsterType == T_ENEMYBEHOLDER)
	{
		srand(time(NULL) + 2);
	}

	numMonster = maxMonster;
	//Initialise
	for (int i = 0; i < numMonster; i++)
	{
		if (monsterPos.size() == 0)
		{
			monsterPos.push_back(Vector3(minPos.x + rand() % (int)(maxPos.x - minPos.x), 0, minPos.z + rand() % (int)(maxPos.z - minPos.z)));
		}
		else
		{
			randX = minPos.x + rand() % (int)(maxPos.x - minPos.x);
			randZ = minPos.z + rand() % (int)(maxPos.z - minPos.z);
			for (int i = 0; i < monsterPos.size(); i++)
			{
				while (randX == monsterPos[i].x && randZ == monsterPos[i].z && randX == playerPos.x && randZ == playerPos.z)
				{
					randX = minPos.x + rand() % (int)(maxPos.x - minPos.x);
					randZ = minPos.z + rand() % (int)(maxPos.z - minPos.z);
				}

			}
			monsterPos.push_back(Vector3(randX, 0, randZ));
		}
	}
}

void monsterManager::add(GameObject*gameobject)
{
	VecMonsterObj.push_back(gameobject);
}

