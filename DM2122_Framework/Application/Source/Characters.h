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
	Characters(Scene*, const string& name, Vector3 &postion, const unsigned &maxHealth);
	Characters(Scene*, const string& name, Vector3 &postion, const unsigned &maxHealth, const unsigned &maxStamina);
	//Characters(Scene*, const string& name, Vector3 &postion, const unsigned &maxHealth, const unsigned &maxStamina,Inventory inventory);
	virtual ~Characters();

	virtual const float getCurrentHealth();
	virtual const float getMaxHealth();
	virtual const float getCurrentStamina();
	virtual const float getMaxStamina();

	virtual void setMaxHealth(const float newMaxHealth);
	virtual void setMaxStamina(const float newMaxStamina);

	virtual void updateHealth(float);
	virtual void updateStamina(float);

	virtual void setDefault();
	virtual bool anyInteraction();
	virtual void render();
	//add on inventory, combat, movement when done
	Inventory inventory_;
private:

	float health_, maxHealth_, stamina_, maxStamina_;
	
};

#endif