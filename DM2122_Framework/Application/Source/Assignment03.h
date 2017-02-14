#ifndef Assignment03_H
#define Assignment03_H

#include "Scene.h"
#include "Camera4.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment03 : public Scene
{
	enum GEOMETRY_TYPE
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
		GEO_TREEBASE,
		GEO_TREE,
		GEO_HOLE,
		GEO_BODY,
		GEO_HEAD,
		GEO_EYE,
		GEO_BB8DETAILS,
		GEO_CYLINDER,
		GEO_CONE,
		GEO_LIGHTBALL,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_MODEL1,
		GEO_MODEL2,
		GEO_ROCK1,
		GEO_ROCK2,
		GEO_ROCK3,
		GEO_ROCK4,
		GEO_ROCK5,
		GEO_BASE,
		GEO_DOOR_R,
		GEO_DOOR_L,
		GEO_TEXT,
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

	};

public:
	Assignment03();
	~Assignment03();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];

	double rotatAngle;
	double translateX;
	double translateY;
	double rotatAngleMartix;
	double scaleAll;
	Camera4 camera;
	MS modelStack, viewStack, projectionStack;

	bool openDoor;
	double translateDoorX;
	bool lightSaberPickedUp;
	Vector3 saberPosition;
	Vector3 handPosition;
	bool saberOn;

	double gravity;

	float FPS;

	bool lightsOn;
	Light light[2];
	void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderSkybox();
	void renderBB8();
	void renderArea1Rocks();

	void DebugCamPosition();
};

#endif