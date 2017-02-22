#ifndef VEIN_H
#define VEIN_H

#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
class Vein : public GameObject
{
public:
	Vein(Scene*, const string&, Vector3&);
	~Vein();

	static void init();
	virtual bool anyInteraction();
	virtual void render();

	 static int numOres;
	 static std::vector<int>iRandXVec;
	 static std::vector<int>iRandYVec;
private:
	
	static int iRandX;
	static int iRandY;
};




#endif