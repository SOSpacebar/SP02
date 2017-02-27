#ifndef WORK_STATIONS_H
#define WORK_STATIONS_H

#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
class WorkStation : public GameObject
{
public:
	enum STATION_TYPE {
		T_TRADE,
		T_FURNACE,
		T_UPGRADE,
	};
	WorkStation(Scene*, const string&, Vector3&, STATION_TYPE station, int rotation);
	~WorkStation();

	virtual bool anyInteraction();
	virtual void render();

	static bool open;
	static bool Topen;
	static bool Fopen;
	static bool Uopen;

private:
};




#endif