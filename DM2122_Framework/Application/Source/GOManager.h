#ifndef GO_MANAGER_H
#define GO_MANAGER_H

#include "GameObject.h"
#include <map>
#include "Camera4.h"



class GameObjectManager
{
public:
	enum GO_TYPE{
		T_ENVIRONMENTAL = 0,
		T_ENEMY,
		T_INTERACTABLE,
		T_PLAYERPROJECTILE ,
		T_MINEABLE,
		T_NUMTYPE //Let NumType be last

	};

	typedef GameObjectManager::GO_TYPE objectType;
	
	GameObjectManager();
	~GameObjectManager();

	void add(objectType type, GameObject* gameObject);
	void remove(GameObject* gameObject);
	void removeAll();

	int GetObjectCount() const;

	void update(Camera4&);

	void renderGameObjects();

	GameObject* get(GameObject* gameObject);
	std::multimap<objectType, GameObject*> _gameObjects;

private:
	
	std::multimap<objectType, GameObject*>::iterator objIt;
	bool updated;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair <objectType, GameObject*> & o) const
		{
			delete o.second;
		}
	};
};















#endif