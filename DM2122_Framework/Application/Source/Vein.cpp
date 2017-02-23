#include "Veins.h"
#include <iostream>
#include "GOManager.h"

int Vein::numOres;
std::vector<int>Vein::iRandXVec;
std::vector<int>Vein::iRandYVec;
int Vein::iRandX;
int Vein::iRandY;


Vein::Vein(Scene* scene, const string& name, Vector3& pos) : GameObject(scene, name, pos)
{
	g_type = Scene::GEO_IRON;
	scale = 2;

	const int objSize = 6;
	Vector3 boxSize(objSize * 2, objSize * 2, objSize * 2);
	this->getCollider().setCollider(pos, boxSize);
}

void Vein::init()
{
	int numOres = 10;
	srand(time(NULL));
	for (int i = 0; i < numOres; i++)
	{
		if (iRandXVec.size() == 0 && iRandYVec.size() == 0)//if its first
		{
			iRandXVec.push_back(rand() % 150);
			iRandYVec.push_back(rand() % 150);
		}
		else//not first
		{
			iRandX = rand() % 150;//get a number
			iRandY = rand() % 150;//get a number
			for (int i = 0; i < iRandXVec.size(); i++)//for all values
			{
				while (iRandX == iRandXVec[i] && iRandY == iRandYVec[i])//if its the same value
				{
					iRandX = rand() % 150;//get a new value
					iRandY = rand() % 150;//get a new value
				}

			}
			iRandXVec.push_back(iRandX);//push new value
			iRandYVec.push_back(iRandY);//push new value
		}
	}
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