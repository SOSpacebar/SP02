#ifndef PLAYER_H
#define PLAYER_H

#include "Characters.h"

class Player : public Characters
{
public:
	Player();
	~Player(){ delete playerInstance; };

	static Player* getInstance();

	void damagePlayer(float);


	void updateOxygen(float);
	void setMaxOxygen(float);
	float getOxygen();
	float getMaxOxygen();

	void update(float);

private:
	bool lackOfOxygen;

	static Player* playerInstance;

	float currentOxygenValue;
	float maxOxygenValue;
};















#endif