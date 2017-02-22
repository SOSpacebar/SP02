#include "Bullet.h"
#include "GOManager.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Scene* scene, const string &name, Vector3 &position, Vector3 &box) : GameObject(scene, name, position + Vector3(-5, 0, 0), box)
{
	g_type = Scene::GEO_CUBE;
	speed_ = 50;
	direction_ = scene->camera.view;
	Vector3 offset = scene->camera.view * 5;
	Vector3 startPos = position + offset;
	position_ = startPos;
}

void Bullet::update()
{
}

bool Bullet::anyInteraction()
{
	position_ += direction_ * speed_ * scene_->dt_;
	this->getCollider().updateColliderPos(this->position_);
	if (position_.x > 100)
	{
		std::cout << "delete";
		scene_->_gameObjectMananger.remove(this);
		return true;
	}
	
	return false;
}

void Bullet::render()
{
	//std::cout << "x " << position_.x << "z " << position_.z;
	scene_->modelStack.PushMatrix();
 	scene_->modelStack.Translate(position_.x, position_.y, position_.z);
	/*scene_->modelStack.Rotate(rotaX, 1, 0, 0);
	scene_->modelStack.Rotate(rotaY, 0, 1, 0);
	scene_->modelStack.Rotate(rotaZ, 0, 0, 1);
	scene_->modelStack.Scale(scale, scale, scale);*/
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable=false);
	scene_->modelStack.PopMatrix();
}
