#include "Walls.h"
#include <iostream>
#include "GOManager.h"



Walls::Walls(Scene* scene, const string& name, Vector3& pos, WALL_TYPE wall, Vector3& rotation,Vector3& scale, Vector3& box) : GameObject(scene, name, pos,box)
{

	if (wall == T_PLAIN)
		g_type = Scene::GEO_ROOM;
	if (wall == T_WINDOW)
		g_type = Scene::GEO_ROOMWINDOW;
	if (wall == T_DOOR)
		g_type = Scene::GEO_ROOMDOOR;
	if (wall == T_TUTORIAL)
		g_type = Scene::GEO_QUAD;
	if (wall == T_TUTORIALDOOR)
		g_type = Scene::GEO_TUTORIALDOOR;


	scalex = scale.x;
	scaley = scale.y;
	scalez = scale.z;
	rotaX = rotation.x;
	rotaY = rotation.y;
	rotaZ = rotation.z;

	this->getCollider().setCollider(pos, box);
}

Walls::~Walls()
{

}

bool Walls::anyInteraction()
{
	auto temp = scene_->_gameObjectMananger._gameObjects.equal_range(GameObjectManager::T_INTERACTABLE);

	for (std::multimap<GameObjectManager::objectType, GameObject*>::iterator it = temp.first; it != temp.second; ++it)
	{
		GameObject* temp = it->second;
		distance_ = (temp->scene_->camera.position - temp->position_).Length();

		if (distance_ < 5 && temp->getName()=="door")
		{
			scene_->camera.position += Vector3(90, 0, 60);
			scene_->camera.target = scene_->camera.position + scene_->camera.view;
			return true;

		}
	}
	return false;
}

void Walls::render()
{
	scene_->modelStack.PushMatrix();
	scene_->modelStack.Translate(position_.x, position_.y, position_.z);
	scene_->modelStack.Rotate(rotaX, 1, 0, 0);
	scene_->modelStack.Rotate(rotaY, 0, 1, 0);
	scene_->modelStack.Rotate(rotaZ, 0, 0, 1);
	scene_->modelStack.Scale(scalex, scaley, scalez);
	scene_->RenderMesh(scene_->meshList[g_type], lightEnable = true);
	scene_->modelStack.PopMatrix();
}