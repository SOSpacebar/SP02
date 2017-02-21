#include "Weapon.h"
#include <iostream>
Weapon::Weapon():weaponDamage_(0), weaponAmmo_(0)
{
}

Weapon::Weapon(Scene* scene, const string&weaponName, Vector3&position, const int weaponDamage, const int weaponAmmo):Item(scene,weaponName,position + Vector3(0, 1, 0)),weaponDamage_(weaponDamage),weaponAmmo_(weaponAmmo)
{
	g_type = Scene::GEO_BLASTER;
}

void Weapon::render()//render this on hand
{
	scene_->modelStack.PushMatrix();
	scene_->modelStack.Translate(position_.x, position_.y, position_.z);//parent the weapon to player
	scene_->modelStack.PushMatrix();
	scene_->modelStack.Rotate(scene_->camera.totalyaw_, 0, -1,0);//left and right
	scene_->modelStack.Rotate(scene_->camera.totalpitch_, 0, 0,-1);//up dow

	scene_->modelStack.Translate(-1, -0.3, -0.3);
	scene_->modelStack.Rotate(180, 0, 0, 1);
	scene_->modelStack.Rotate(90, 1, 0, 0);
	scene_->modelStack.Scale (0.03, 0.03, 0.03);

	scene_->RenderMesh(scene_->meshList[g_type], lightEnable);
	scene_->modelStack.PopMatrix();
	scene_->modelStack.PopMatrix();
}

bool Weapon::anyInteraction()
{
	position_.x = scene_->camera.position.x;
	position_.y = scene_->camera.position.y;
	position_.z = scene_->camera.position.z;
	return false;
}

Weapon::~Weapon()
{
}