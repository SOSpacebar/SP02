#ifndef ITEM_H
#define ITEM_H

using namespace std;
class Item
{
public:
	Item();
	~Item();

	//private:
	//protected:

	//initialize to 0 as default
	int size = 0;
	int weight = 0;
	int durability = 0;
	int damage = 0;
};

Item::Item()
{
}

Item::~Item()
{
}

#endif