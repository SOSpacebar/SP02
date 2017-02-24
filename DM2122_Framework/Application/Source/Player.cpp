#include "Player.h"

Player *Player::playerInstance = 0; // Singleton Handle


Player* Player::getInstance() {
	if (!playerInstance) 
		playerInstance = new Player();

	return playerInstance;
}

Player::Player() : Characters(), maxOxygenValue(300)
{
	currentOxygenValue = maxOxygenValue;
	setDefault();
}

void Player::damagePlayer(double value)
{
	if (getCurrentHealth() > 0)
		updateHealth(value);
}

void Player::updateOxygen(double value)
{
	if (currentOxygenValue > maxOxygenValue)
		return;

	if (currentOxygenValue < maxOxygenValue * 0.1)
		lackOfOxygen = true;

	currentOxygenValue += value;
}

void Player::setMaxOxygen(double value)
{
	maxOxygenValue = value;
}

int Player::getOxygen()
{
	return (int)currentOxygenValue;
}

int Player::getMaxOxygen()
{
	return (int)maxOxygenValue;
}

void Player::update(double dt)
{
	if (currentOxygenValue > 0)
		updateOxygen(dt);

	if (lackOfOxygen)
		updateHealth(10 * dt);
}
