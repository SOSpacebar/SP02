
#ifndef BULLET_H
#define BULLET_H
#include <Vector3.h>

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init(const Vector3 &position, const float &directionHorizontal_, const float &directionVertical_, const float &speed);
	void updateBullet(double deltaTime);

	Vector3 position;
	float directionHorizontal_;
	float directionVertical_;
	float speed_;

private:

	
};
#endif 
