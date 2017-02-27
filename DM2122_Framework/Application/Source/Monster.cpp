#include "Monster.h"
#include "GOManager.h"
#include "Bullet.h"

Monster::Monster(Scene* scene, const string&name, Vector3&position, const int &health) : Characters(scene, name, position, health)
{
}

Monster::Monster(Scene* scene, const string&name, Vector3&position, const int &health, const int &damage) : Characters(scene, name, position, health), damage(0)
{
}

Monster::Monster(Scene* scene, const string& name, Vector3& pos, MONSTER_TYPE monster) : Characters(scene, name, pos)
{
	if (monster == T_ENEMYPROBE)
	{
		g_type = Scene::GEO_ALIENPROBE;
		acceleration_ = 2.f;
		maxSpeed = 20.f;
		attackDistance = 10;
		setDamage(5);
		setMaxHealth(100);
		attackTimer = 3;
	}
	if (monster == T_ENEMYBEHOLDER)
	{
		g_type = Scene::GEO_BEHOLDER;
		acceleration_ = 10.f;
		maxSpeed = 50.f;
		attackDistance = 30;
		setDamage(10);
		setMaxHealth(200);
		attackTimer = 5;
	}

	scale = 0.3;
	const int objSize = 1;
	Vector3 boxSize(objSize * 2, objSize * 5, objSize * 2); //2,5,2
	this->getCollider().setCollider(pos, boxSize);
	timer = 0;
}

bool Monster::anyInteraction()
{
	//if (nearestMonsterPos == 0)
		nearestMonsterPos = &position_;

	Vector3 distanceToPlayer = scene_->camera.position - position_; 
	float distanceToPlayerLength = distanceToPlayer.Length();
	Vector3 nearestToPlayer = *(nearestMonsterPos)-scene_->camera.position;

	timer += scene_->dt_;
	if (nearestToPlayer.LengthSquared() >= distanceToPlayer.LengthSquared())
		nearestMonsterPos = &position_;

	Vector3 thisDistance = distanceToPlayer.Normalized();

	//Rotate to face player.
	rotaY = -Math::RadianToDegree(atan2(distanceToPlayer.z, distanceToPlayer.x)) + 45;
	
	if (speed < maxSpeed)
		speed += acceleration_ * scene_->dt_;

	//AI States Checker
	if (distanceToPlayerLength > 45) {
		currentState = AI_CHASE;
	}
	else if (distanceToPlayerLength <= 45) {
		currentState = AI_ATTACK;
	}
	else {
		currentState = AI_IDLE;
	}

	switch (currentState)
	{
	case Monster::AI_IDLE:
		break;
	case Monster::AI_CHASE:

		if (distanceToPlayerLength >= attackDistance)
			thisDistance *= 2;
		else
			thisDistance.SetZero();

		break;
	case Monster::AI_ATTACK:
		
		float dirX = Math::RadianToDegree(atan2(distanceToPlayer.y, distanceToPlayer.Length()));

		if (distanceToPlayerLength <= attackDistance) {
			if (timer >= attackTimer) {
				//scene_->_gameObjectMananger.add(GameObjectManager::objectType::T_PLAYERPROJECTILE, new Bullet(this->scene_, "Bullet", position_, Vector3(dirX, rotaY, 0)));
				std::cout << "enemy pew";
				attackTimer = timer + attackInterval;
			}

			thisDistance.SetZero(); // Stay stationary while firing
		}
		break;
	}

	// Prevent this unit from merging with others WIP
	/*auto temp = scene_->_gameObjectMananger._gameObjects.equal_range(GameObjectManager::T_ENEMY);

	for (std::multimap<GameObjectManager::objectType, GameObject*>::iterator it = temp.first; it != temp.second; ++it)
	{
		GameObject* temp = it->second;
		Vector3 hitDirection;

		if (temp != this && getCollider().checkHit(temp->getCollider(), &hitDirection) == true)
			position_ += -hitDirection * scene_->dt_;
	}

	position_.x += thisDistance.x * speed * scene_->dt_;
	position_.y += thisDistance.y  * speed * scene_->dt_;
	position_.z += thisDistance.z  * speed * scene_->dt_;

	
	if (getCurrentHealth() <= 0)
	{
		scene_->_gameObjectMananger.remove(this);
		std::cout << "dead";
		return true;
	}*/

	return false;
}

Monster::~Monster()
{
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