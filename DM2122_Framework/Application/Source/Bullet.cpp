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

	//auto mappy = _scene->objBuilder.objInteractor._objects.equal_range(td_OBJ_TYPE::TYPE_ENEMY);

	//for (multimap<td_OBJ_TYPE, Object*>::iterator it = mappy.first; it != mappy.second; ++it) {

	//	Object* temp = it->second;

	//	// NPC bullet collision
	//	if ((temp->position - position).Length() < _interactDistance) {

	//		NPC* npc = dynamic_cast<NPC*>(temp);
	//		Vector3 pushAway = (npc->position - _scene->camera.position).Normalized();
	//		pushAway *= 5; // multiply the unit vector by 5 so we can push him further

	//		// Damage the enemy and then remove this bullet
	//		//npc->position += pushAway;
	//		npc->reduceHealth(_bulletDamage);
	//		npc->reduceVelocity(npc->getCurrentVelocity() / 2);

	//		_scene->objBuilder.destroyObject(this);
	//		return true;
	//	}

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
