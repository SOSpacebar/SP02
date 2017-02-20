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

const unsigned Characters::getCurrentHealth()
{
	return this->health_;
}

const unsigned Characters::getMaxHealth()
{
	return this->maxHealth_;
}

const unsigned Characters::getCurrentStamina()
{
	return this->stamina_;
}

const unsigned Characters::getMaxStamina()
{
	return this->maxStamina_;
}

void Characters::setMaxHealth(const unsigned newMaxHealth)
{
	this->maxHealth_ = newMaxHealth;
}

void Characters::setMaxStamina(const unsigned newMaxStamina)
{
	this->maxStamina_ = newMaxStamina;
}

bool Characters::anyInteraction()
{
	return false;
}

void Characters::render()
{

}