#include "Veins.h"
#include <iostream>
#include "GOManager.h"



Vein::Vein(Scene* scene, const string& name, Vector3& pos, ORE_TYPE ore) : GameObject(scene, name, pos)
{
	if (ore == T_COAL)
		g_type = Scene::GEO_COAL;
	if (ore == T_IRON)
		g_type = Scene::GEO_IRON;
	if (ore == T_COBALT)
		g_type = Scene::GEO_COBALT;

	scale = 0.5;
	const int objSize = 1;
	Vector3 boxSize(objSize * 1, objSize * 5, objSize * 1);
	this->getCollider().setCollider(pos, boxSize);
}

Vein::~Vein()
{

}

bool Vein::anyInteraction()
{
	auto temp = scene_->_gameObjectMananger._gameObjects.equal_range(GameObjectManager::T_MINEABLE);

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

void Vein::render()
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