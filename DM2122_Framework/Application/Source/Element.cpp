
#include "Element.h"


void Element::setProperties(const int& size, const int& durability, const int& weight)
{
	this->size = size;
	this->durability = durability;
	this->weight = weight;
}

const int Element::getDurability()
{
	return durability;
}
const int Element::getweight()
{
	return weight;
}
const int Element::getsize()
{
	return size;
}



//Element steel;//Materials does not do damage
//steel.setProperties(2, 3, 4);//(size,weight,durability)

////size for inventory capacity
////weight to slow player down when "strength of player "cannot carry anything heavier---> if(strength<weight carrying) walk slower


////durability is when the item breaks and cannot be used...basically disappears from inventory when durability==0(turns to dust..unable for further use/cannot be fixed)
//when a certain item breaks, turns into base elements, if base elements break cannot be used at all