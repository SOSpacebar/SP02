#ifndef BULLET_H
#define BULLET_H
#include <Vector3.h>
#include "Application.h"
#include "GameObject.h"
class Bullet : public GameObject
{
public:	
	Bullet();
	~Bullet();

	Bullet(Scene*, const string &name, Vector3 &position, Vector3 &box);
	Bullet(Scene*, const string &name, Vector3 &position, Vector3 rotation, Vector3 direction, Vector3 &box);

	float speed_;

	Vector3 direction_;
	Vector3 startPosition;
	Vector3 bulletDirection_;

	virtual void update();
	virtual void render();

	virtual bool anyInteraction();

private:
	bool isEnemyBullet;

	
};
#endif 
