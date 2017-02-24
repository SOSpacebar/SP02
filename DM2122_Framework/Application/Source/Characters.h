#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "GameObject.h"
#include "Inventory.h"
//using namespace std;
class Characters : public GameObject
{
public:
	Characters();
	Characters(Scene*, const string& name);
	Characters(Scene*, const string& name, Vector3 &postion);
	Characters(Scene*, const string& name, Vector3 &postion, const double &maxHealth);
	Characters(Scene*, const string& name, Vector3 &postion, const double &maxHealth, const double &maxStamina);
	//Characters(Scene*, const string& name, Vector3 &postion, const unsigned &maxHealth, const unsigned &maxStamina,Inventory inventory);
	virtual ~Characters();

	virtual const int getCurrentHealth();
	virtual const int getMaxHealth();
	virtual const int getCurrentStamina();
	virtual const int getMaxStamina();

	virtual void setMaxHealth(const double newMaxHealth);
	virtual void setMaxStamina(const double newMaxStamina);

	virtual void updateHealth(double);
	virtual void updateStamina(double);

	virtual void setDefault();
	virtual bool anyInteraction();
	virtual void render();
	//add on inventory, combat, movement when done
	Inventory inventory_;
private:

	double health_, maxHealth_, stamina_, maxStamina_;
	
};

#endif