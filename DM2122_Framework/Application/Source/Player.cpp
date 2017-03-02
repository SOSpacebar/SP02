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
	lackOfOxygen = false;
	setDefault();
}

void Player::damagePlayer(double value)
{
	if (getInstance()->getCurrentHealth() > 0)
		getInstance()->updateHealth(value);
}

void Player::updateOxygen(double value)
{
	getInstance()->currentOxygenValue += value;

	 if (getInstance()->currentOxygenValue > getInstance()->maxOxygenValue)
		getInstance()->currentOxygenValue = getInstance()->maxOxygenValue;

	if (getInstance()->currentOxygenValue < getInstance()->maxOxygenValue * 0.1)
		getInstance()->lackOfOxygen = true;	
}

void Player::setMaxOxygen(double value)
{
	getInstance()->maxOxygenValue = value;
}

int Player::getOxygen()
{
	return (int)getInstance()->currentOxygenValue;
}

int Player::getMaxOxygen()
{
	return (int)getInstance()->maxOxygenValue;
}

void Player::update(double dt)
{
	if (getInstance()->currentOxygenValue > 0 && !inBase)
		getInstance()->updateOxygen(dt * 3);

	if (getInstance()->currentOxygenValue < getInstance()->maxOxygenValue && inBase)
		getInstance()->updateOxygen(-dt * 3);

	if (getInstance()->lackOfOxygen)
		getInstance()->updateHealth(3 * dt);

	if (inBase && getInstance()->getCurrentHealth() < getInstance()->getMaxHealth())
		updateHealth(-dt * 3);

	if (getInstance()->isRunning == true)
	{
		getInstance()->updateStamina(3 * dt);
		scene_->camera.speed_ = 45;
		getInstance()->recoverStamina = 0;
		getInstance()->isRunning = false;
	}

	else
	{
		if (getInstance()->recoverStamina < 3)
		{
			getInstance()->recoverStamina -= dt;
		}

		else
			getInstance()->updateStamina(-dt);

		scene_->camera.speed_ = 30;
	}
}
void Player::setplayerstat(double health, double oxy, double stam)//health,oxy,stamina
{
	getInstance()->setMaxHealth(health);
	getInstance()->setMaxOxygen(oxy);
	getInstance()->setMaxStamina(stam);
}

float Player::getOxygenbar()
{
	return (getInstance()->currentOxygenValue / getInstance()->maxOxygenValue) * 30;
}
float Player::getHealthBar()
{
	return (getInstance()->getCurrentHealth() / getInstance()->maxHealth_) * 30;
}

float Player::getStaminabar()
{
	return (getInstance()->getCurrentStamina() / getInstance()->maxStamina_) * 30;
}

void Player::setDefault()
{
	this->maxHealth_ = 100;
	this->maxStamina_ = 50;
	this->health_ = maxHealth_;
	this->stamina_ = maxStamina_;
	this->maxOxygenValue = 300;
	this->currentOxygenValue = maxOxygenValue;
}