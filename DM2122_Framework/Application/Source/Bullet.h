
#ifndef BULLET_H
#define BULLET_H
#include <Vector3.h>
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void Init(const Vector3 &position, const float &directionHorizontal_, const float &directionVertical_, const float &speed);
	Bullet(Scene*, const string &name, Vector3 &position, Vector3 &box);
	void updateBullet(double deltaTime);

	float directionHorizontal_;
	float directionVertical_;
	float speed_;
	
	virtual void update();
	virtual void render();

	virtual bool anyInteraction();

private:

	
};
#endif 
