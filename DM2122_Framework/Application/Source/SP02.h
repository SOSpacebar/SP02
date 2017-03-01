#ifndef SP02_H
#define SP02_H

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
#include "monsterManager.h"
#include "Player.h"

class SP02 : public Scene
{
	/*enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_HEMISPHERE,
		GEO_SPHERE,
		GEO_CYLINDER,
		GEO_CONE,
		GEO_LIGHTBALL,
		GEO_ROOM,
		GEO_ROOMDOOR,
		GEO_TEXT,
		GEO_SPACE,
		GEO_SUN,
		GEO_MOON,
		GEO_COAL,
		GEO_IRON,
		GEO_COBALT,
		NUM_GEOMETRY,
	};

	enum UNIFROM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_NUMLIGHTS,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,

	};*/

public:
	SP02();
	~SP02();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	/*unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];*/

	//static GameObjectManager _gameObjectMananger;

	//Camera4 camera;
	/*MS modelStack, viewStack, projectionStack;*/

	bool lightsOn;
	Light light[2];

	float FPS;
	//daily cycle
	float dailycycle;

	//void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderSkybox();

	//void DebugCamPosition();

	float time = 10;
	double count = 0;
	float reloadTime = 0;
	float rotateStimpak;
	//Player player;
	//test
	//Characters player;
};
#endif