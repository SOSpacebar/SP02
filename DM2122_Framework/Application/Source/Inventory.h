#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <map>
#include "Characters.h"
using namespace std;

class Inventory:public Characters
{
public:
	Inventory();
	virtual ~Inventory();
	void add(string name);//only adds upquantity of existing element
	void push(string name, unsigned int);//places element in container with specific quantity
	void pop(string name);//clears the element from container,the whole quantity
	void minus(string name);//decrease quantity by 1
	unsigned int size();//output different TYPES of elements
	void print();//show container in the interface


	map<string, unsigned int>container;//the container
	unsigned int getquantity;//to get quantity of element inside the container 


};

Inventory::Inventory()
{

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

#endif