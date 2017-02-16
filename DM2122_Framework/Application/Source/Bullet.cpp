#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(const Vector3&position, const float&rotation)
{
	this->position = position;
	this->rotation = rotation;
}

void Bullet::updateBullet(double deltaTime)
{
	position.x += (float)(10 * cos(Math::DegreeToRadian(rotation))*deltaTime);
	position.z += (float)(10 * cos(Math::DegreeToRadian(rotation))*deltaTime);
}
