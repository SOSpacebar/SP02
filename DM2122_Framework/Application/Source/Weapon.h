#ifndef WEAPON_H
#define WEAPON_H

//#include<string>
#include "Item.h"
//using std::string;
class Weapon : public Item
{
public:
	Weapon();
	Weapon(Scene* scene, const string&weaponName, Vector3&position, const int weaponDamage, const int weaponAmmo);
	~Weapon();

	void render();
	bool anyInteraction();

private:
	const int weaponDamage_;
	const int weaponAmmo_;
};

#endif