#ifndef TUTORIAL_SCENE_H
#define TUTORIAL_SCENE_H

#include "Scene.h"
#include "Camera4.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Characters.h"
#include "Bullet.h"
#include "Weapon.h"
#include "GOManager.h"
#include "UIManager.h"
#include "Veins.h"
#include "EnvironmentManager.h"

class TScene : public Scene
{
	

public:
	TScene();
	~TScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	
	bool lightsOn;
	Light light[2];

	float FPS;
	//daily cycle
	float dailycycle;
	//coal
	int randomx;
	int randomz;
	int RandXArray[150];
	int RandZArray[150];
	//iron
	int irandomx;
	int irandomz;
	int IRandXArray[100];
	int IRandZArray[100];
	//cobalt
	int crandomx;
	int crandomz;
	int CRandXArray[50];
	int CRandZArray[50];




	//void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderSkybox();

	bool canFire = false;

	void DebugCamPosition();



	//test
	Characters player;
};
#endif