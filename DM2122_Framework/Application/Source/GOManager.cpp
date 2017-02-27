#include "GOManager.h"
#include <algorithm>  

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	//for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
	if (_gameObjects.size()) {
		for (auto &i : _gameObjects)
			delete i.second;
	}
	_gameObjects.clear();
}

void GameObjectManager::add(objectType type, GameObject* gameObject)
{
	_gameObjects.insert(std::pair<objectType, GameObject*>(type, gameObject));
}

void GameObjectManager::remove(GameObject* gameObject)
{
	std::multimap<objectType, GameObject*> &temp = _gameObjects;

	for (auto &it = temp.begin(); it != temp.end(); ++it)
	{
		if (it->second == gameObject)
		{
			it = _gameObjects.erase(it);
			objIt = it;
			updated = true;
			delete gameObject;
			return;
		}
	}
}

void GameObjectManager::removeAll() //REMOVE FROM PREVS SCREEN
{
	if (_gameObjects.size()) {
		for (auto &i : _gameObjects)
			delete i.second;
	}

	_gameObjects.clear();
}

void GameObjectManager::update(Camera4& cam)
{
	objIt = _gameObjects.begin();

	static Vector3 prevPosition;
	static Vector3 prevTarget;
	static float prevTPitch_;
	static float prevTYaw_;


	for (objIt; objIt != _gameObjects.end();)
	{
		GameObject* temp = objIt->second;
		
		//Check For Interaction Of Objects
		if (!temp->anyInteraction())
		{
			Vector3 lastHitPos = 0;
			//Check For Player Collision
			if (temp->getCollider().checkHit(cam.getCollider(), &lastHitPos) && objIt->first != T_PLAYERPROJECTILE && objIt->first != T_ENEMY)
			{
				std::cout << temp->getName(); //Check what collider its hitting
				cam.position = prevPosition;
				cam.target = prevTarget;
				cam.totalpitch_ = prevTPitch_;
				cam.totalyaw_ = prevTYaw_;
			}
		}

		if (!updated)
			objIt++;
		else
			updated = false;
	}

	prevPosition = cam.position;
	prevTarget = cam.target;
	prevTPitch_ = cam.totalpitch_;
	prevTYaw_ = cam.totalyaw_;
}

GameObject* GameObjectManager::get(GameObject* gameObject)
{
	std::multimap<objectType, GameObject*> &temp = _gameObjects;

	for (auto &it = temp.begin(); it != temp.end(); it++)
	{
		if (it->second == gameObject)
		{
			return it->second;
		}
	}

	return NULL;
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::renderGameObjects()
{
	for (auto &i : _gameObjects)
	{
		i.second->render();
	}
}