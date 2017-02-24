#ifndef VEIN_H
#define VEIN_H

#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
class Vein : public GameObject
{
public:
	enum ORE_TYPE {
		T_COAL,
		T_IRON,
		T_COBALT,
		T_NUMTYPE,
	};
	Vein(Scene*, const string&, Vector3&,ORE_TYPE ore,int rotation);
	~Vein();

	virtual bool anyInteraction();
	virtual void render();

private:
};




#endif