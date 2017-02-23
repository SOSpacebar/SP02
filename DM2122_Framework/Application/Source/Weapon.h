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

private:
	const int weaponDamage_;
	const int weaponAmmo_;
};

#endif