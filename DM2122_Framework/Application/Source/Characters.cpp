#include "Characters.h"

Characters::Characters() : GameObject(), health_(0), stamina_(0), maxHealth_(0), maxStamina_(0)
{

}

Characters::Characters(const string& name) : GameObject(name), health_(0), stamina_(0), maxHealth_(0), maxStamina_(0)
{
}

Characters::Characters(const string& name, Vector3 &postion) : GameObject(name, postion), health_(0), stamina_(0), maxHealth_(0), maxStamina_(0)
{

}

Characters::Characters(const string& name, Vector3 &postion, const unsigned &maxhealth_) : GameObject(name, postion), health_(maxhealth_), stamina_(0), maxHealth_(maxhealth_), maxStamina_(0)
{

}

Characters::Characters(const string& name, Vector3 &postion, const unsigned &maxhealth_, const unsigned &maxStamina) : GameObject(name, postion), health_(maxhealth_), stamina_(maxStamina), maxHealth_(maxhealth_), maxStamina_(maxStamina)
{

}

Characters::~Characters()
{

}

void Characters::setDefault()
{
	maxHealth_ = 100;
	maxStamina_ = 50;
	health_ = maxHealth_;
	stamina_ = maxStamina_;
}