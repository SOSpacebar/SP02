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
Characters::Characters(Scene* scene, const string& name, Vector3 &postion, const double &maxhealth_) : GameObject(scene, name, postion), health_(maxhealth_), stamina_(0), maxHealth_(maxhealth_), maxStamina_(0)
{

}

Characters::Characters(Scene* scene, const string& name, Vector3 &postion, const double &maxhealth_, const double &maxStamina) : GameObject(scene, name, postion), health_(maxhealth_), stamina_(maxStamina), maxHealth_(maxhealth_), maxStamina_(maxStamina)
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

const int Characters::getCurrentHealth()
{
	return (int)this->health_;
}

const int Characters::getMaxHealth()
{
	return (int)this->maxHealth_;
}

const int Characters::getCurrentStamina()
{
	return (int)this->stamina_;
}

const int Characters::getMaxStamina()
{
	return (int)this->maxStamina_;
}

void Characters::setMaxHealth(const double newMaxHealth)
{
	this->maxHealth_ = newMaxHealth;
	health_ = maxHealth_;
}

void Characters::setMaxStamina(const double newMaxStamina)
{
	this->maxStamina_ = newMaxStamina;
	stamina_ = maxStamina_;
}

void Characters::updateHealth(double value)
{
	if (health_ > maxHealth_)
		health_ = maxHealth_;

	this->health_ += value;
}

void Characters::updateStamina(double value)
{
	if (stamina_ <= maxStamina_)
		this->stamina_ += value;
	else
		this->stamina_ = maxStamina_;
}



bool Characters::anyInteraction()
{
	return false;
}

void Characters::render()
{

}