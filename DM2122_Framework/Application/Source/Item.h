#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
using namespace std;
class Item:public GameObject
{
public:
	Item();//default constructor
	Item(Scene* scene,const string&name);
	~Item();

	//private:
	//protected:

	//initialize to 0 as default (initialize in constructorrrrrr)
	int size = 0;
	int weight = 0;
	int durability = 0;
	int damage = 0;
	//Item has damage
	//Item has durability
	//Item has size
	//Item has weight
	//but NOT/CANNOT BE DEFINED!!!
};
#endif