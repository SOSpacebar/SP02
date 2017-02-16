#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"
#include <string>
#include "Collider.h"

#endif

using std::string;

class GameObject
{
public:
	GameObject();
	GameObject(const string &name);
	GameObject(const string &name, Vector3 &position);
	GameObject(const string &name, Vector3 &position, Vector3 &boxSize);
	virtual ~GameObject();

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 newPosition);
	virtual string getName();

	virtual void setCollider(Collider*);
	virtual Collider* getCollider();
private:
	Vector3 position_;
	const string name_;
	Collider* collisionBox_;
};

