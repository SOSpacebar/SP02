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
	recoverStamina = 0;
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

	if (isRunning)
	{
		updateStamina(dt * 3);
		scene_->camera.speed_ = 45;
		recoverStamina = 0;
		isRunning = false;
	}

	else
	{
		if (recoverStamina < 3)
		{
			recoverStamina -= dt;
		}

		else
			updateStamina(-dt);

		scene_->camera.speed_ = 30;
	}
}
void  Player::setplayerstat(double health, double oxy, double stam)//health,oxy,stamina
{
	setMaxHealth(health);
	setMaxOxygen(oxy);
	setMaxStamina(stam);
}