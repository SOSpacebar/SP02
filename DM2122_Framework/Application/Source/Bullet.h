
#ifndef BULLET_H
#define BULLET_H
#include <Vector3.h>
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	Bullet(Scene*, const string &name, Vector3 &position, Vector3 &box);

	float speed_;

	Vector3 direction_;
	
	virtual void update();
	virtual void render();

	virtual bool anyInteraction();

private:

	
};
#endif 
