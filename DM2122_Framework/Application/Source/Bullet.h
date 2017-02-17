
#ifndef BULLET_H
#define BULLET_H
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
#endif 
