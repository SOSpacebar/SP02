#include "Player.h"

Player *Player::playerInstance = 0; // Singleton Handle


Player* Player::getInstance() {
	if (!playerInstance) 
		playerInstance = new Player();

	return playerInstance;
}

Player::Player() : Characters(), currentOxygenValue(maxOxygenValue), maxOxygenValue(300)
{
	setDefault();
}

void Player::damagePlayer(float value)
{
	if (getCurrentHealth() > 0)
		updateHealth(value);
}

void Player::updateOxygen(float value)
{
	if (currentOxygenValue < maxOxygenValue)
		currentOxygenValue += value;

	if (currentOxygenValue < maxOxygenValue * 0.1)
		lackOfOxygen = true;
}

void Player::setMaxOxygen(float value)
{
	maxOxygenValue = value;
}

float Player::getOxygen()
{
	return currentOxygenValue;
}

float Player::getMaxOxygen()
{
	return maxOxygenValue;
}

void Player::update(float dt)
{
	if (lackOfOxygen)
		updateHealth(10 * dt);
}
