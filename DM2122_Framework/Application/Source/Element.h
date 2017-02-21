#ifndef ELEMENT_H
#define ELEMENT_H


#include "Item.h"
//commented of setters and int that are independent
//commented are singleton
//im using multiple task of same purpose...setting something might as well set all the properties


//damage commented incase for future use
class Element :public Item
{
public:
	Element();
	~Element();

	//	virtual void setdamage(const int&);//damage
	//	virtual void setsize(const int&);//size
	//	virtual void setdurability(const int&);//durability
	//	virtual void setweight(const int&);//weight
	//virtual void setProperties(const int&, const int&, const int&, const int&);
	virtual void setProperties(const int&, const int&, const int&);

	//const int getDamage();
	const int getDurability();
	const int getweight();
	const int getsize();
private:

	/*int size;
	int weight;
	int durability;
	int damage;*/
};
#endif


//Element steel;//Materials does not do damage
//steel.setProperties(2, 3, 4);//(size,weight,durability)

////size for inventory capacity
////weight to slow player down when "strength of player "cannot carry anything heavier---> if(strength<weight carrying) walk slower


////durability is when the item breaks and cannot be used...basically disappears from inventory when durability==0(turns to dust..unable for further use/cannot be fixed)
//when a certain item breaks, turns into base elements, if base elements break cannot be used at all