#ifndef TSCENE_H
#define TSCENE_H

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
#include <fstream>

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
	bool isPaused;
	bool nextScene;
	int stage;
	int textoffset;
	Light light[2];
	float FPS;
	//daily cycle
	float dailycycle;
	void RenderSkybox();
	//test
	Characters player;
	std::vector<string> tutorialtext;
};
#endif