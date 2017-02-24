#include "EnvironmentManager.h"
std::vector<Vector3>EnvironmentManager::orePos;

EnvironmentManager::EnvironmentManager()//constructor
{
}

EnvironmentManager::~EnvironmentManager()//destructon
{
}

void EnvironmentManager::initRandPos(ENVIRONMENT_TYPE oreType, int maxOres, Vector3 playerPos,Vector3 MinPos,Vector3 MaxPos)//store rand pos
{
	//clear previous data
	for (int i = 0; !orePos.empty(); i++)
		orePos.pop_back();
	//get diff rand() seed
	if (oreType == T_COAL)
	{
		srand(time(NULL));
	}
	if (oreType == T_IRON)
	{
		srand(time(NULL) * 2);
	}
	if (oreType == T_COBALT)
	{
		srand(time(NULL) *3);
	}
	//rand num of ores
	numOres = rand() % maxOres;
	//init ores
	for (int i = 0; i < numOres; i++)
	{
		if (orePos.size() == 0)//if its first
		{
			orePos.push_back(Vector3(MinPos.x + rand() % (int)(MaxPos.x - MinPos.x), 0, MinPos.z + rand() % (int)(MaxPos.z- MinPos.z)));
		}
		else//not first
		{
			RandX = MinPos.x + rand() % (int)(MaxPos.x - MinPos.x);//get a number
			RandZ = MinPos.z + rand() % (int)(MaxPos.z - MinPos.z);//get a number
			for (int i = 0; i < orePos.size(); i++)//for all values
			{
				while (RandX == orePos[i].x && RandZ == orePos[i].z && RandX == playerPos.x && RandZ == playerPos.z)//if its the same value or at player postion
				{
					RandX = MinPos.x + rand() % (int)(MaxPos.x - MinPos.x);//get a new value
					RandZ = MinPos.z + rand() % (int)(MaxPos.z - MinPos.z);//get a new value
				}

			}
			orePos.push_back(Vector3(RandX, 0, RandZ));
		}
	}

	for (int i = 0; i < orePos.size(); i++) //checking if it stores values into vector
		std::cout << orePos[i] << " ore " << std::endl;

	std::cout << orePos.size() << std::endl;

}

void EnvironmentManager::add(GameObject* gameobject)//store game obj
{
	VecEnvObj.push_back(gameobject);
}
