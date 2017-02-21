#include "Item.h"
Item::Item()//default constructor
{}
Item::~Item()//destructor
{}

Item::Item(Scene* scene, const string&name, Vector3&position):GameObject(scene,name,position)
{

}