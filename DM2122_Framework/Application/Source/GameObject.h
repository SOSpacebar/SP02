#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"
#include <string>
#include "Collider.h"
#include "Scene.h"

using std::string;

class GameObject
{
public:
	GameObject();
	GameObject(Scene*, const string &name);
	GameObject(Scene*, const string &name, Vector3 &position);
	GameObject(Scene*, const string &name, Vector3 &position, Vector3 &box);
	virtual ~GameObject();
	
	virtual bool anyInteraction() = 0;
	virtual void update();
	//virtual void collisionDetected() = 0;
	virtual void render() = 0;

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 newPosition);
	virtual void updatePosition(Vector3 newPosition);
	virtual string getName();

	virtual void setCollider(Collider);
	virtual Collider& getCollider();

	unsigned g_type;
	Scene* scene_;
	Vector3 position_;
	float rotaX = 0, rotaY = 0, rotaZ = 0;
	float scale = 1;
	bool lightEnable = true;
private:

	const string name_;
	Collider collisionBox_;
};


#endif
