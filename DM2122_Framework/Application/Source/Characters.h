#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "GameObject.h"


class Characters : GameObject
{
public:
	Characters();
	Characters(const string& name);
	Characters(const string& name, Vector3 &postion);
	Characters(const string& name, Vector3 &postion, const unsigned &maxHealth);
	Characters(const string& name, Vector3 &postion, const unsigned &maxHealth, const unsigned &maxStamina);
	virtual ~Characters();

	virtual const unsigned getCurrentHealth();
	virtual const unsigned getMaxHealth();
	virtual unsigned getCurrentStamina();
	virtual unsigned getMaxStamina();

	virtual void setMaxHealth(const unsigned newMaxHealth);
	virtual void setMaxStamina(const unsigned newMaxStamina);

	virtual void setDefault();

	//add on inventory, combat, movement when done
	
private:
	unsigned health_, maxHealth_, stamina_, maxStamina_;
};

#endif