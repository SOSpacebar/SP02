#define WEAPON_H
#ifndef WEAPON_H

#endif
#include<string>
using std::string;
class Weapon
{
public:
	Weapon(const string&weaponName,const int weaponDamage);
	~Weapon();

private:
	const int attackDamage;
};

//Weapon::Weapon(const string&weaponName, const int weaponDamage)
//{
//}
//
//Weapon::~Weapon()
//{
//}