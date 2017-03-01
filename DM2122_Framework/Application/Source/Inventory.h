#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <map>
//#include "Characters.h"
using namespace std;

class Inventory
{
public:
	Inventory();
	virtual ~Inventory();
	void add(string name);//only adds upquantity of existing element
	void push(string name, unsigned int);//places element in container with specific quantity
	void pop(string name);//clears the element from container,the whole quantity
	void minus(string name);//decrease quantity by 1
	void upgrade(string name, unsigned int);//upgrade the item name,amount to decrease
	void trade(string name, string name2, unsigned int buy, unsigned int sell);//buying,selling,amount buy,amount sell
	void melt(string name,unsigned int, double dt);
	void reset();
	unsigned int size();//output different TYPES of elements
	void print();//show container in the interface

	
	map<string, unsigned int>container;//the container
	unsigned int getquantity;//to get quantity of element inside the container 
	unsigned int gettype;

};
#endif