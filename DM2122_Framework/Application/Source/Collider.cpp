#include "Collider.h"

Collider::Collider() : boxMin(0), boxMax(0)
{
}

Collider::Collider(Vector3 min, Vector3 max) : boxMin(min), boxMax(max)
{

}

Collider::~Collider()
{

}

bool Collider::OnCollisionEnter(Collider& other)
{
	if (this->boxMax != NULL || this->boxMin != NULL || other.boxMax != NULL || other.boxMin != NULL)
		if ((this->boxMin.x <= other.boxMax.x && this->boxMax.x >= other.boxMin.x) && 
			(this->boxMin.y <= other.boxMax.y && this->boxMax.y >= other.boxMin.y) &&
			(this->boxMin.z <= other.boxMax.z && this->boxMax.z >= other.boxMin.z))
		{
			std::cout << "OUCH";
			return true;
		}

	return false;
}