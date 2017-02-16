#define BULLET_H
#ifndef BULLET_H

#endif 

#include <Vector3.h>

class Bullet
{
public:
	Bullet();
	~Bullet();
	Vector3 position;

	void Init(const Vector3 &position, const float &rotation);
	void updateBullet(double deltaTime);

	float rotation;

private:

	
};