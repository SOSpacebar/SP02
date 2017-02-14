#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

GameObject::GameObject(const string& name) : name_(name)
{
}

GameObject::GameObject(const string& name, Vector3 position) : name_(name), position_(position)
{

}

string GameObject::getName()
{
	return this->name_;
}

void GameObject::setPosition(Vector3 newPosition)
{
	this->position_ = newPosition;
}

Vector3 GameObject::getPosition()
{
	return this->position_;
}