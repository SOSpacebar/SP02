#ifndef VEIN_H
#define VEIN_H

#include "GameObject.h"

class Vein : public GameObject
{
public:
	Vein(Scene*, const string&, Vector3&);
	~Vein();

	virtual bool anyInteraction();
	virtual void render();


private:
	
};




#endif