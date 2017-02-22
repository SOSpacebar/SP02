#include "Item.h"
Item::Item()//default constructor
{}
Item::~Item()//destructor
{}

Item::Item(Scene* scene, const string&name):GameObject(scene,name)
{

}