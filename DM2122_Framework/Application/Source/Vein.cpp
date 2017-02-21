#include "Veins.h"

Vein::Vein(Scene* scene, const string& name, Vector3& pos) : GameObject(scene, name, pos)
{
	g_type = Scene::GEO_IRON;
	scale = 2;

	const int objSize = 6;
	Vector3 boxSize(objSize * 2, objSize * 2, objSize * 2);
	this->getCollider().setCollider(pos, boxSize);
}

Vein::~Vein()
{

}

bool Vein::anyInteraction()
{

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