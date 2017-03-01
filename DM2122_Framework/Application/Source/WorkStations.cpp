#include "WorkStations.h"
#include <iostream>
#include "GOManager.h"

bool WorkStation::open;
bool WorkStation::Topen;
bool WorkStation::Fopen;
bool WorkStation::Uopen;


WorkStation::WorkStation(Scene* scene, const string& name, Vector3& pos, STATION_TYPE station, int rotation) : GameObject(scene, name, pos)
{
	if (station == T_TRADE)
	{
		g_type = Scene::GEO_TRADER;
	}
	if (station == T_FURNACE)
	{
		g_type = Scene::GEO_CUBE;
	}
	if (station == T_UPGRADE)
	{
		g_type = Scene::GEO_UPGRADER;
	}
	rotaY = rotation;
	scale = 2;
	open = false;
	const int objSize = 5;
	Vector3 boxSize(objSize * 1, objSize * 1, objSize * 1);
	this->getCollider().setCollider(pos, boxSize);	
}

WorkStation::~WorkStation()
{

}

bool WorkStation::anyInteraction()
{
	auto temp = scene_->_gameObjectMananger._gameObjects.equal_range(GameObjectManager::T_INTERACTABLE);

	for (std::multimap<GameObjectManager::objectType, GameObject*>::iterator it = temp.first; it != temp.second; ++it)
	{
		GameObject* temp = it->second;
		distance_ = (temp->scene_->camera.position - temp->position_).Length();

		if (distance_ < 15 && scene_->interact)
		{
			if (open == true)
			{
				open = false;
				Topen = false;
				Fopen = false;
				Uopen = false;
			}
			else if (open == false)
				open = true;

			std::cout << distance_ << temp->getName() << open << std::endl;
			//interactions
			if (temp->getName() == "trader" && open)
			{
				std::cout << "TOPEN" << std::endl;
				Topen = true;
			}
			if (temp->getName() == "furnace" && open)
			{
				std::cout << "FOPEN" << std::endl;
				Fopen = true;
			}
			if (temp->getName() == "upgrader" && open)
			{
				std::cout << "UOPEN" << std::endl;
				Uopen = true;

			}
			scene_->interact = false;
			return true;
		}
	}

	scene_->interact = false;
	return false;
}

void WorkStation::render()
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