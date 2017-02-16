#define WEAPON_H
#ifndef WEAPON_H

#endif
#include<string>
#include "Item.h"
using std::string;
class Weapon : public Item
{
public:
	Weapon(const string&weaponName, const int weaponDamage, const int weaponAmmo);
	~Weapon();

private:
	const int attackDamage;
	const int ammoSize;
};

