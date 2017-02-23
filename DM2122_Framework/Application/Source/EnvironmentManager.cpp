#include "EnvironmentManager.h"
std::vector<Vector3>EnvironmentManager::orePos;

EnvironmentManager::EnvironmentManager()//constructor
{
}

EnvironmentManager::~EnvironmentManager()//destructon
{
}

void EnvironmentManager::initRandPos(ENVIRONMENT_TYPE oreType)//store rand pos
{
	srand(time(NULL));
	if (oreType == T_COAL)
	{
		numOres = rand() % 30;
		for (int i = 0; i < numOres; i++)
		{
			if (RandXVec.size() == 0 && RandZVec.size() == 0)//if its first
			{
				RandXVec.push_back(rand() % 150);
				RandZVec.push_back(rand() % 150);
			}
			else//not first
			{
				RandX = rand() % 150;//get a number
				RandZ = rand() % 150;//get a number
				for (int i = 0; i < RandXVec.size(); i++)//for all values
				{
					while (RandX == RandXVec[i] && RandZ == RandZVec[i])//if its the same value
					{
						RandX = rand() % 150;//get a new value
						RandZ = rand() % 150;//get a new value
					}

				}
				RandXVec.push_back(RandX);//push new value
				RandZVec.push_back(RandZ);//push new value
			}
		}
		for (int i = 0; i < numOres; i++)
			orePos.push_back(Vector3(RandXVec[i], 0, RandZVec[i]));
		for (int i  = 0; i < orePos.size(); i++) //checking if it stores values into vector
			std::cout << Vector3(RandXVec[i], 0, RandZVec[i] )<< std::endl;

	}
}

void EnvironmentManager::add(GameObject* gameobject)//store game obj
{
	VecEnvObj.push_back(gameobject);
}
