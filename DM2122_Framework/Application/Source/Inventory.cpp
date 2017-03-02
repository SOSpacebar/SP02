
#include "Inventory.h"
#include <time.h>

Inventory::Inventory()//must initialize all pick up items in a container as 0
{
	container.insert(make_pair("Iron", 0));
	container.insert(make_pair("Copper", 0));
	container.insert(make_pair("Silver", 0));
	container.insert(make_pair("Gold", 0));
	container.insert(make_pair("Steel", 0));
	container.insert(make_pair("Coal", 0));
	container.insert(make_pair("Cobalt", 0));
	container.insert(make_pair("Scrap", 0));

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

void Inventory::upgrade(string name,unsigned int quantity)
{
	getquantity = container.find(name)->second;
	if ((getquantity - quantity) >= NULL)
	{
		getquantity = getquantity - quantity;
		container.erase(name);
		container.insert(make_pair(name, getquantity));

	}
}
void Inventory::trade(string name,string name2, unsigned int quantity, unsigned int quantity2)
{
		//update inventory bought,increase
		getquantity = (container.find(name)->second)+quantity;
		container.erase(name);
		container.insert(make_pair(name, getquantity));
		//update sold
		getquantity = (container.find(name2)->second) - quantity2;
		container.erase(name2);
		container.insert(make_pair(name2, getquantity));

}
void Inventory::melt(string name,unsigned int quantity,double dt)
{
	//update inventory ,decrease
	getquantity = (container.find(name)->second) - quantity;
	container.erase(name);
	container.insert(make_pair(name, getquantity));

	//srand(time(NULL));
	gettype = rand() % (container.size()-1);
	//container.erase(container(gettype))
	string name2;
	if (gettype == 0)
	{
		name2 = "Coal";
		
	}
	else if (gettype == 1)
	{
		name2 = "Cobalt";
	}
	else if (gettype == 2)
	{
		name2 = "Copper";
	}
	else if (gettype == 3)
	{
		name2 = "Gold";
	}
	else if (gettype == 4)
	{
		name2 = "Iron";
	}
	else if (gettype == 5)
	{
		name2 = "Silver";
		
	}
	else if (gettype == 6)
	{
		name2 = "Steel";

	}
	else
	{
		//recieve nothing
	}
	getquantity = (container.find(name2)->second) + quantity*10;
	container.erase(name2);
	container.insert(make_pair(name2, getquantity));
}
void Inventory::reset()//must initialize all pick up items in a container as 0
{
	container.clear();
	container.insert(make_pair("Iron", 0));
	container.insert(make_pair("Copper", 0));
	container.insert(make_pair("Silver", 0));
	container.insert(make_pair("Gold", 0));
	container.insert(make_pair("Steel", 0));
	container.insert(make_pair("Coal", 0));
	container.insert(make_pair("Cobalt", 0));
	container.insert(make_pair("Scrap", 0));

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
