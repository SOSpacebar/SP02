#include "Monster.h"
#include "GOManager.h"

Monster::Monster(Scene* scene, const string&name, Vector3&position, const int &health) : Characters(scene, name, position), health(0)
{
}

Monster::Monster(Scene* scene, const string&name, Vector3&position, const int &health, const int &damage) : Characters(scene, name, position), health(0), damage(0)
{
}

Monster::Monster(Scene* scene, const string& name, Vector3& pos, MONSTER_TYPE monster) : Characters(scene, name, pos)
{
	if (monster == T_ENEMYPROBE)
		g_type = Scene::GEO_ALIENPROBE;
	if (monster == T_ENEMYBEHOLDER)
		g_type = Scene::GEO_BEHOLDER;
	
	scale = 0.5;
	const int objSize = 6;
	Vector3 boxSize(objSize * 2, objSize * 2, objSize * 2);
	this->getCollider().setCollider(pos, boxSize);
}

bool Monster::anyInteraction()
{
	auto temp = scene_->_gameObjectMananger._gameObjects.equal_range(GameObjectManager::T_ENEMY);

	for (std::multimap<GameObjectManager::objectType, GameObject*>::iterator it = temp.first; it != temp.second; ++it)
	{
		GameObject* temp = it->second;
		distance_ = (temp->scene_->camera.position - temp->position_).Length();

		if (distance_ < 20 && scene_->interact)
		{
			scene_->interact = false;
			scene_->_gameObjectMananger.remove(temp);
			return true;
		}
	}

	scene_->interact = false;
	return false;
}

Monster::~Monster()
{
}

void Monster::setHealth(int hp)
{
	this->health = hp;
}

int Monster::getHealth()
{
	return this->health;
}

void Monster::setDamage(int att)
{
	this->damage = att;
}

int Monster::getDamage()
{
	return this->damage;
}

void Monster::render()
{
	scene_->modelStack.PushMatrix();
	scene_->modelStack.Translate(position_.x, position_.y, position_.z);
	scene_->modelStack.Rotate(rotaX, 1, 0, 0);
	scene_->modelStack.Rotate(rotaY, 0, 1, 0);
	scene_->modelStack.Rotate(rotaZ, 0, 0, 1);
	scene_->modelStack.Scale(scale, scale, scale);
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable = false);
	scene_->modelStack.PopMatrix();
}