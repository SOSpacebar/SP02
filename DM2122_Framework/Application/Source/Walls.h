#ifndef WALLS_H
#define WALLS_H

#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

class Walls : public GameObject
{
public:
	enum WALL_TYPE {
		T_PLAIN,
		T_WINDOW,
		T_DOOR,
		T_TUTORIAL,
		T_TUTORIALDOOR,
		T_NUMTYPE,
	};
	Walls(Scene*, const string&, Vector3&, WALL_TYPE wall , Vector3& rotation, Vector3& scale,Vector3& box);
	~Walls();

	virtual bool anyInteraction();
	virtual void render();

private:
	int scalex;
	int scaley;
	int scalez;
	Vector3 boxSize;
};




#endif