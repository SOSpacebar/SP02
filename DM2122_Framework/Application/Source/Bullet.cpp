#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Scene* scene, const string &name, Vector3 &position, Vector3 &box) : GameObject(scene, name, position+Vector3(5,0,5), box)
{
	g_type = Scene::GEO_CUBE;
	directionHorizontal_ = scene->camera.pitch_;
	speed_ = 10;
	
}

//void Bullet::Init(const Vector3&position, const float &directionHorizontal, const float &directionVertical, const float&speed)
//{
//	//this->position = position;
//	//this->directionHorizontal_ = directionHorizontal;
//	//this->directionVertical_ = directionVertical;
//	//this->speed_ = speed;
//}

void Bullet::update()
{
	/*position.x += (float)(speed_ * cos(Math::DegreeToRadian(directionHorizontal_)) * scene_->_dt);
	position.z += (float)(speed_ * sin(Math::DegreeToRadian(directionHorizontal_)) * scene_->_dt);*/
}

bool Bullet::anyInteraction()
{
	position.x += (float)(speed_ * cos(Math::DegreeToRadian(directionHorizontal_)) * scene_->_dt);
	position.z += (float)(speed_ * sin(Math::DegreeToRadian(directionHorizontal_)) * scene_->_dt);
	return false;
}

void Bullet::render()
{
	std::cout << position.z;
	scene_->modelStack.PushMatrix();
 	scene_->modelStack.Translate(position_.x, position_.y, position_.z);
	scene_->modelStack.Rotate(rotaX, 1, 0, 0);
	scene_->modelStack.Rotate(rotaY, 0, 1, 0);
	scene_->modelStack.Rotate(rotaZ, 0, 0, 1);
	scene_->modelStack.Scale(5, 5, 5);
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable);
	scene_->modelStack.PopMatrix();
}
