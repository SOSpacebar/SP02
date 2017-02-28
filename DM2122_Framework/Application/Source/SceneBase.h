#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Camera4.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Characters.h"
#include "WorkStations.h"
#include "Walls.h"
#include "Bullet.h"
#include "Weapon.h"
#include "GOManager.h"
#include "UIManager.h"
#include "EnvironmentManager.h"
#include "Player.h"

class SceneBase : public Scene
{

public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:

	float tsmthhappened;
	bool bsmthhappend;
	bool lightsOn;
	Light light[2];
	float FPS;
	float dailycycle;
	void RenderSkybox();

	//upgrade
	int WDcount;
	int WAcount;
	int OxyCount;
	int StaCount;
	int HPCount;
	//upgrade cost
	int IronCost;
	int CobaltCost;
	//set upgrade
	double OX;
	double HP;
	double ST;

	//trade
	int Goldcnt;//1
	int Silvercnt;//2
	int Ironcnt;//3
	int Steelcnt;//4
	int Cobaltcnt;//5
	int Coppercnt;//6
	int Coalcnt;//7
	//trade cost
	int GoldCOST;//1
	int SilverCOST;//2
	int IronCOST;//3
	int SteelCOST;//4
	int CobaltCOST;//5
	int CopperCOST;//6
	
	//Furnace
	int Scrapcnt;
	
};
#endif