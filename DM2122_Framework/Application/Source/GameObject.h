#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"
#include <string>

#endif

using std::string;

class GameObject
{
public:
	GameObject();
	GameObject(const string &name);
	GameObject(const string &name, Vector3 position);
	virtual ~GameObject();

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 newPosition);
	virtual string getName();
private:
	Vector3 position_;
	const string name_;
	//CollisionHandler collisionBox;
};

