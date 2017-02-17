#include "Collider.h"

Collider::Collider() : boxMin(0), boxMax(0), boxSize(0)
{
}

Collider::Collider(Vector3 min, Vector3 max, Vector3 boxSize) : boxMin(min - boxSize * 0.5f), boxMax(max + boxSize * 0.5f), boxSize(boxSize)
{

}

Collider::~Collider()
{

}

bool Collider::OnCollisionEnter(Collider& other)
{
	if (this->boxMax != NULL || this->boxMin != NULL || other.boxMax != NULL || other.boxMin != NULL)
		if ((this->boxMin.x < other.boxMax.x && this->boxMax.x > other.boxMin.x) && 
			(this->boxMin.y < other.boxMax.y && this->boxMax.y > other.boxMin.y) &&
			(this->boxMin.z < other.boxMax.z && this->boxMax.z > other.boxMin.z))
		{
			return true;
		}

	return false;
}

Vector3 Collider::getboxSize()
{
	return this->boxSize;
}

void Collider::updateColliderPos(Vector3& newPos)
{
	if (this->boxMax !=NULL || this->boxMin !=NULL)
	{
		boxMin = (newPos - boxSize * 0.5f);
		boxMax = (newPos + boxSize * 0.5f);
	}
}