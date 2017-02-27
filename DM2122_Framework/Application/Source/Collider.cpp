#include "Collider.h"

Collider::Collider() : boxMin(0), boxMax(0), boxSize(0)
{
}

Collider::Collider(Vector3* pos, Vector3 boxSize) : boxMin((-boxSize * 0.5f) + *pos), boxMax((boxSize * 0.5f) + *pos), boxSize(boxSize), position(pos)
{

}

Collider::~Collider()
{

}

bool Collider::checkHit(Collider& other, Vector3* direction)
{
	if (this->boxMax != NULL || this->boxMin != NULL || other.boxMax != NULL || other.boxMin != NULL)
		if ((this->boxMin.x < other.boxMax.x && this->boxMax.x > other.boxMin.x) && 
			(this->boxMin.y < other.boxMax.y && this->boxMax.y > other.boxMin.y) &&
			(this->boxMin.z < other.boxMax.z && this->boxMax.z > other.boxMin.z))
		{
			Vector3 hitPos = other.position - position;
			//std::cout << "inside";
			if (direction != nullptr)
			{
				if (hitPos != 0)
				{
					(*direction) = hitPos.Normalized();
					//std::cout << "direction";
				}
			}
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
		*position = newPos;
	}
}

void Collider::setCollider(Vector3 pos,Vector3 boxSize)
{
	boxMin = -boxSize + pos;
	boxMax = boxSize + pos;
}