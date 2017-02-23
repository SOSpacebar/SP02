#include "Characters.h"

Characters::Characters() : GameObject(), health_(0), stamina_(0), maxHealth_(0), maxStamina_(0)
{

}

Characters::Characters(Scene* scene, const string& name) : GameObject(scene,name), health_(0), stamina_(0), maxHealth_(0), maxStamina_(0)
{
}

Characters::Characters(Scene* scene, const string& name, Vector3 &postion) : GameObject(scene, name, postion), health_(0), stamina_(0), maxHealth_(0), maxStamina_(0)
{
	g_type = Scene::GEO_CUBE;
}
Characters::Characters(Scene* scene, const string& name, Vector3 &postion, const unsigned &maxhealth_) : GameObject(scene,name, postion), health_(maxhealth_), stamina_(0), maxHealth_(maxhealth_), maxStamina_(0)
{

}

Characters::Characters(Scene* scene, const string& name, Vector3 &postion, const unsigned &maxhealth_, const unsigned &maxStamina) : GameObject(scene,name, postion), health_(maxhealth_), stamina_(maxStamina), maxHealth_(maxhealth_), maxStamina_(maxStamina)
{

}


Characters::~Characters()
{

}

void Characters::setDefault()
{
	this->maxHealth_ = 100;
	this->maxStamina_ = 50;
	this->health_ = maxHealth_;
	this->stamina_ = maxStamina_;
}

const float Characters::getCurrentHealth()
{
	return this->health_;
}

const float Characters::getMaxHealth()
{
	return this->maxHealth_;
}

const float Characters::getCurrentStamina()
{
	return this->stamina_;
}

const float Characters::getMaxStamina()
{
	return this->maxStamina_;
}

void Characters::setMaxHealth(const float newMaxHealth)
{
	this->maxHealth_ = newMaxHealth;
}

void Characters::setMaxStamina(const float newMaxStamina)
{
	this->maxStamina_ = newMaxStamina;
}

void Characters::updateHealth(float value)
{
	this->health_ += value;
}

void Characters::updateStamina(float value)
{
	this->stamina_ += value;
}



bool Characters::anyInteraction()
{
	return false;
}

void Characters::render()
{

}