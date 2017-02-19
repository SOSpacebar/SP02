#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(const Vector3&position, const float &directionHorizontal, const float &directionVertical, const float&speed)
{
	this->position = position;
	this->directionHorizontal_ = directionHorizontal;
	//this->directionVertical_ = directionVertical;
	this->speed_ = speed;
}

void Bullet::updateBullet(double deltaTime)
{
	position.x += (float)(speed_ * cos(Math::DegreeToRadian(directionHorizontal_))*deltaTime);
	position.z += (float)(speed_ * sin(Math::DegreeToRadian(directionHorizontal_))*deltaTime);
}

