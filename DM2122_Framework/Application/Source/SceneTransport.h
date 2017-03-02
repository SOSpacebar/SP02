#ifndef SCENETRANSPORT_H
#define SCENETRANSPORT_H

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
#include "Player.h"

class Transport : public Scene
{
public:
	Transport();
	~Transport();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	bool lightsOn;
	Light light[2];

	float loadTime;

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

};
#endif