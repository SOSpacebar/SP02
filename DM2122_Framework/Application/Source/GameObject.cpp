#include "GameObject.h"

GameObject::GameObject() : name_(""), position_(0), collisionBox_()
{
	
}

GameObject::GameObject(Scene* scene, const string &name) : scene_(scene), name_(name), collisionBox_()
{

}

GameObject::GameObject(Scene* scene, const string &name, Vector3 &position) : scene_(scene), name_(name), position_(position), collisionBox_(&position, Vector3(20, 10, 20))
{
	
}

GameObject::GameObject(Scene* scene, const string &name, Vector3 &position, Vector3 &boxSize) : scene_(scene), name_(name), position_(position), collisionBox_(&position, boxSize)
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
	scene_->modelStack.PushMatrix();
	scene_->modelStack.Translate(position_.x, position_.y, position_.z);
	scene_->modelStack.Rotate(rotaX, 1, 0, 0);
	scene_->modelStack.Rotate(rotaY, 0, 1, 0);
	scene_->modelStack.Rotate(rotaZ, 0, 0, 1);
	scene_->modelStack.Scale(scale, scale, scale);
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable);
	scene_->modelStack.PopMatrix();
}

void GameObject::update()
{

}