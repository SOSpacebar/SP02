#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Scene* scene, const string &name, Vector3 &position, Vector3 &box) : GameObject(scene, name, position + Vector3(1,0,1), box)
{
	g_type = Scene::GEO_CUBE;
	directionHorizontal_ = scene->camera.yaw_;
	directionVertical_ = scene->camera.pitch_; 
	speed_ = 5;
}


void Bullet::update()
{
}

bool Bullet::anyInteraction()
{
	position_.x += (float)(speed_ * cos(Math::DegreeToRadian(directionHorizontal_)) * scene_->_dt);
	position_.z += (float)(speed_ * sin(Math::DegreeToRadian(directionHorizontal_)) * scene_->_dt);
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
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable);
	scene_->modelStack.PopMatrix();
}
