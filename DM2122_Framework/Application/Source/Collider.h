#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector3.h"

class Collider
{
public:
	Collider();
	~Collider();
	Collider(Vector3*, Vector3);

	
	void updateColliderPos(Vector3&);
	void setCollider(Vector3,Vector3);
	bool checkHit(Collider&, Vector3* = nullptr);
	Vector3 getboxSize();
	
	Vector3* position;
private:
	Vector3 boxMin, boxMax, boxSize;
	
};





#endif