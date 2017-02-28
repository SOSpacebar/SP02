#ifndef PLAYER_H
#define PLAYER_H

#include "Characters.h"

class Player : public Characters
{
public:
	Player();
	~Player(){ delete playerInstance; };

	static Player* getInstance();

	void damagePlayer(double);

	void setplayerstat(double, double, double);//health,oxygen,stamina


	void updateOxygen(double);
	void setMaxOxygen(double);
	int getOxygen();
	int getMaxOxygen();

	void update(double);

	bool isRunning;

private:
	bool lackOfOxygen;

	static Player* playerInstance;

	double currentOxygenValue;
	double maxOxygenValue;
	float recoverStamina;
};

#endif