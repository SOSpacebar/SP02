#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector3.h"

class Collider
{
public:
	Collider();
	~Collider();
	Collider(Vector3, Vector3);

	bool OnCollisionEnter(Collider&);
private:
	Vector3 boxMin, boxMax;
};





#endif