//In progress,not called
#ifndef AI_H
#define AI_H

#include "Monster.h"
class AI: public Monster
{
public:

private:
	float mindistance = 1;
	float maxvisibledistance = 30;
	float movespeed = 2.5;
	float runningstartdistance = 10;
	Vector3 player;
	Vector3 monster;
};




//
//class AI
//{
//public:
//
//	
//private:
//	
//	float mindistance = 1;
//	float visibility = 20;
//	float startrun = 5;
//	float movespeed = 1.5f;
//
//	Vector3 player;
//	Vector3 monster;
//};
#endif

