#include "GameObject.h"

GameObject::GameObject() : name_(""), position_(0), collisionBox_()
{
	
}

GameObject::GameObject(const string &name) : name_(name), collisionBox_()
{

}

GameObject::GameObject(const string &name, Vector3 &position) : name_(name), position_(position)
{
	Vector3 boxSize(10, 10, 10);
	Collider* c = new Collider(position - boxSize, position + boxSize);
	GameObject::setCollider(c);
}

GameObject::GameObject(const string &name, Vector3 &position, Vector3 &boxSize) : name_(name), position_(position)
{
	Collider* c = new Collider(position - boxSize, position + boxSize);
	GameObject::setCollider(c);
}

GameObject::~GameObject()
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

void GameObject::setCollider(Collider* c)
{
	collisionBox_ = c;
}

Collider* GameObject::getCollider()
{
	return this->collisionBox_;
}