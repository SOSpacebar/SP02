
#include "Inventory.h"


Inventory::Inventory()//must initialize all pick up items in a container as 0
{
	container.insert(make_pair("Iron", 0));
	container.insert(make_pair("Copper", 0));
	container.insert(make_pair("Silver", 0));
	container.insert(make_pair("Gold", 0));
	container.insert(make_pair("Steel", 0));
}

Inventory::~Inventory()
{
}
void Inventory::add(string name)
{

	getquantity = container.find(name)->second;
	++getquantity;
	container.erase(name);
	container.insert(make_pair(name, getquantity));
}
void Inventory::push(string name, unsigned int quantity)
{
	container.insert(make_pair(name, quantity));

	getquantity = container.find(name)->second + quantity;
	container.erase(name);
	container.insert(make_pair(name, getquantity));
}
void Inventory::pop(string name)
{
	container.erase(name);
}
void Inventory::minus(string name)
{
	getquantity = container.find(name)->second;
	if (getquantity <= 0)
	{
		getquantity = 0;
	}
	else
	{
		--getquantity;
	}


	container.erase(name);
	container.insert(make_pair(name, getquantity));
}
unsigned int Inventory::size()
{
	int types = 0;
	types = container.size();
	return types;
}

void Inventory::print()
{
	for (map<string, unsigned int>::const_iterator it = container.begin(); it != container.end(); ++it)
	{
		cout << it->second << " quantity of " << it->first << endl;
	}

}
