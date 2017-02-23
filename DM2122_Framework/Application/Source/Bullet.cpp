#include "Bullet.h"
#include "GOManager.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Scene* scene, const string &name, Vector3 &pos, Vector3&box) :GameObject(scene, name, pos, box)
{
	g_type = Scene::GEO_LASERPROJ;
	speed_ = 50;
	bulletDirection_ = scene->camera.view;
	startPosition = position_;

}

void Bullet::update()
{
}

bool Bullet::anyInteraction()
{
	
	position_ += bulletDirection_* speed_ * scene_->dt_;
	this->getCollider().updateColliderPos(this->position_);
	float distance = (startPosition - this->position_).Length();

	if (distance > 50)
	{
		scene_->_gameObjectMananger.remove(this);
		std::cout << "delete" << std::endl;
		return true;
	}
	else if (Application::cantSpam == true)
	{
		Application::mouseClicked = false;
		
	}
	return false;
}

void Bullet::render()
{
	scene_->modelStack.PushMatrix();
	scene_->modelStack.PushMatrix();
	scene_->modelStack.Translate(position_.x, position_.y, position_.z);//bullet moving
	scene_->modelStack.Rotate(scene_->camera.totalyaw_, 0, -1, 0);//left and right
	scene_->modelStack.Rotate(scene_->camera.totalpitch_, 0, 0, -1);//up down
	scene_->modelStack.Translate(-4, -1, 0);// offset distance
	scene_->modelStack.Scale(scale, scale, scale);
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable = false);
	scene_->modelStack.PopMatrix();
	scene_->modelStack.PopMatrix();


}
