#include "Bullet.h"
#include "GOManager.h"
#include "Player.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Scene* scene, const string &name, Vector3 &pos, Vector3&box) : GameObject(scene, name, pos, box)
{
	g_type = Scene::GEO_LASERPROJ;
	speed_ = 50;
	bulletDirection_ = scene->camera.view;
	startPosition = position_;

}

Bullet::Bullet(Scene* scene, const string &name, Vector3 &position, Vector3 rotation, Vector3 direction, Vector3 &box) : GameObject(scene, name, position, box)
{
	g_type = Scene::GEO_LASERPROJ;
	speed_ = 50;
	bulletDirection_ = direction;
	startPosition = position + direction;
	isEnemyBullet = true;
	rotaX = rotation.x;
	rotaY = rotation.y;
	rotaZ = rotation.z;
}

void Bullet::update()
{
}

bool Bullet::anyInteraction()
{
	if (isEnemyBullet)
	{
		if (getCollider().checkHit(scene_->camera.getCollider()))
		{
			Player::getInstance()->updateHealth(-5);
			scene_->_gameObjectMananger.remove(this);
			return true;
		}
	}

	else
	{
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

		auto temp = scene_->_gameObjectMananger._gameObjects.equal_range(GameObjectManager::T_ENEMY);

		for (std::multimap<GameObjectManager::objectType, GameObject*>::iterator it = temp.first; it != temp.second; ++it)
		{
			GameObject* temp = it->second;
			distance_ = (temp->position_ - position_).Length();

			if (distance_ < 5)
			{
				scene_->_gameObjectMananger.remove(temp);
				scene_->_gameObjectMananger.remove(this);
				return true;
			}
		}
	}

	position_ += bulletDirection_* speed_ * scene_->dt_;
	this->getCollider().updateColliderPos(this->position_);

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
