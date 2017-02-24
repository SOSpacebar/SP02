#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item
{
public:
	Weapon();
	Weapon(Scene* scene, const string&weaponName, const int weaponDamage, const int weaponAmmo);
	~Weapon();

	void render();
	bool anyInteraction();
	static int weaponDamage_;
	static int weaponAmmo_;

private:

};

#endif