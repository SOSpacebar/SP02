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
	//clear previous data
	for (int i = 0; !orePos.empty(); i++)
		orePos.pop_back();

	//COAL
	if (oreType == T_COAL)
	{
		srand(time(NULL));

		numOres = rand() % 30;
		for (int i = 0; i < numOres; i++)
		{
			if (orePos.size() == 0)//if its first
			{
				orePos.push_back(Vector3(rand()%150, 0, rand()%150));
			}
			else//not first
			{
				RandX = rand() % 150;//get a number
				RandZ = rand() % 150;//get a number
				for (int i = 0; i < orePos.size(); i++)//for all values
				{
					while (RandX == orePos[i].x && RandZ == orePos[i].z)//if its the same value
					{
						RandX = rand() % 150;//get a new value
						RandZ = rand() % 150;//get a new value
					}

				}
				orePos.push_back(Vector3(RandX, 0, RandZ));
			}
		}

		for (int i = 0; i < orePos.size(); i++) //checking if it stores values into vector
			std::cout << orePos[i] << " coal " << std::endl;

		std::cout << orePos.size() << std::endl;

	}
	//IRON
	if (oreType == T_IRON)
	{
		srand(time(NULL)*2);

		numOres = rand() % 20;//get a number
		for (int i = 0; i < numOres; i++)
		{
			if (orePos.size() == 0)//if its first
			{
				orePos.push_back(Vector3(rand() % 150, 0, rand() % 150));//push initial value
			}
			else//not first
			{
				RandX = rand() % 150;//get a number
				RandZ = rand() % 150;//get a number
				for (int i = 0; i < orePos.size(); i++)//for all values
				{
					while (RandX == orePos[i].x && RandZ == orePos[i].z)//if its the same value
					{
						RandX = rand() % 150;//get a new value
						RandZ = rand() % 150;//get a new value
					}

				}
				orePos.push_back(Vector3(RandX, 0, RandZ));//push value
			}
		}

		for (int i = 0; i < orePos.size(); i++) //checking if it stores values into vector
			std::cout << orePos[i] << " iron " << std::endl;
		std::cout << orePos.size() << std::endl;
	}
	if (oreType == T_COBALT)
	{
		srand(time(NULL)*3);

		numOres = rand() % 10;//get a number
		for (int i = 0; i < numOres; i++)
		{
			if (orePos.size() == 0)//if its first
			{
				orePos.push_back(Vector3(rand() % 150, 0, rand() % 150));//push initial value
			}
			else//not first
			{
				RandX = rand() % 150;//get a number
				RandZ = rand() % 150;//get a number
				for (int i = 0; i < orePos.size(); i++)//for all values
				{
					while (RandX == orePos[i].x && RandZ == orePos[i].z)//if its the same value
					{
						RandX = rand() % 150;//get a new value
						RandZ = rand() % 150;//get a new value
					}

				}
				orePos.push_back(Vector3(RandX, 0, RandZ));//push value
			}
		}

		for (int i = 0; i < orePos.size(); i++) //checking if it stores values into vector
			std::cout << orePos[i] << " iron " << std::endl;
		std::cout << orePos.size() << std::endl;
	}
}

void EnvironmentManager::add(GameObject* gameobject)//store game obj
{
	VecEnvObj.push_back(gameobject);
}
