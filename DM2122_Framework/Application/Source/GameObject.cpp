#include "GameObject.h"

GameObject::GameObject() : name_(""), position_(0), collisionBox_()
{
	
}

GameObject::GameObject(const string &name) : name_(name), collisionBox_()
{

}

GameObject::GameObject(const string &name, Vector3 &position) : name_(name), position_(position), collisionBox_(&position, Vector3(20,10,20))
{
}

GameObject::GameObject(const string &name, Vector3 &position, Vector3 &boxSize) : name_(name), position_(position)
{
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

void GameObject::setCollider(Collider c)
{
	collisionBox_ = c;
}

Collider& GameObject::getCollider()
{
	return this->collisionBox_;
}

void GameObject::updatePosition(Vector3 newPosition)
{
	this->position_ = newPosition;
}

void GameObject::render()
{
	//_scene->modelStack.PushMatrix();
	//_scene->modelStack.Translate(position_.x, position_.y, position_.z);
	//_scene->modelStack.Rotate(rotationX, 1, 0, 0);
	//_scene->modelStack.Rotate(rotationY, 0, 1, 0);
	//_scene->modelStack.Rotate(rotationZ, 0, 0, 1);
	//_scene->modelStack.Scale(scale, scale, scale);
	//_scene->RenderMesh(_scene->meshList[type], lights);
	//_scene->modelStack.PopMatrix();
}