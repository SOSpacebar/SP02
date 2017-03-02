#include "TScene.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "SceneManager.h"
#include "MyMath.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

TScene::TScene()
{
}

TScene::~TScene()
{
}

void TScene::Init()
{
	//init text file and line
	tsmthhappened = 0;
	bsmthhappend = false;

	string line;
	ifstream myfile("Text/Tutorial.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			tutorialtext.push_back(line);
		}
		myfile.close();
	}
	Application::mouseClicked = false;
	stage = 1;
	dailycycle = 0;
	textoffset = 1;
	//Application::mouseClicked = false;
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable Camera
	//camera.Init(Vector3(40, 5, -115), Vector3(0, 5, -115), Vector3(0, 1, 0));
	camera.Init(Vector3(40, 5,-115), Vector3(0, 5, -115), Vector3(0, 1, 0));

	// Init VBO here
	FPS = 0;
	lightsOn = true;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1, 1);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Tscene-walls.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_QUAD]->material.kShininess = 3.f;

	meshList[GEO_TUTORIALDOOR] = MeshBuilder::GenerateQuad("door", Color(1, 1, 1), 1, 1);
	meshList[GEO_TUTORIALDOOR]->textureID = LoadTGA("Image//door.tga");
	meshList[GEO_TUTORIALDOOR]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_TUTORIALDOOR]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_TUTORIALDOOR]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TUTORIALDOOR]->material.kShininess = 1.f;

	meshList[GEO_SPACE] = MeshBuilder::GenerateQuad("space", Color(1, 1, 1), 1, 1);
	meshList[GEO_SPACE]->textureID = LoadTGA("Image//Space.tga");
	meshList[GEO_SUN] = MeshBuilder::GenerateQuad("sun", Color(1, 1, 1), 1, 1);
	meshList[GEO_SUN]->textureID = LoadTGA("Image//SpaceSun.tga");
	meshList[GEO_MOON] = MeshBuilder::GenerateQuad("moon", Color(1, 1, 1), 1, 1);
	meshList[GEO_MOON]->textureID = LoadTGA("Image//SpaceMoon.tga");

	meshList[GEO_BLASTER] = MeshBuilder::GenerateOBJ("blaster", "OBJ//blaster.obj");
	meshList[GEO_BLASTER]->textureID = LoadTGA("Image//blasterblue.tga");
	meshList[GEO_BLASTER]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_BLASTER]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BLASTER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLASTER]->material.kShininess = 1.f;

	meshList[GEO_LASERPROJ] = MeshBuilder::GenerateOBJ("laserProj", "OBJ//laserProjectile.obj");
	meshList[GEO_LASERPROJ]->textureID = LoadTGA("Image//laserProjectileRed.tga");

	meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND] = MeshBuilder::GenerateQuad("uibackground", Color(1, 1, 1), 1, 1);
	meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND]->textureID = LoadTGA("Image//uiBackground.tga");
	meshList[GEO_HEALTHBAR] = MeshBuilder::GenerateQuad("health", Color(1, 1, 1), 1, 1);
	meshList[GEO_HEALTHBAR]->textureID = LoadTGA("Image//healthBar.tga");
	meshList[GEO_OXYGENBAR] = MeshBuilder::GenerateQuad("oxygen", Color(1, 1, 1), 1, 1);
	meshList[GEO_OXYGENBAR]->textureID = LoadTGA("Image//oxygenBar.tga");
	meshList[GEO_STAMINABAR] = MeshBuilder::GenerateQuad("stamina", Color(1, 1, 1), 1, 1);
	meshList[GEO_STAMINABAR]->textureID = LoadTGA("Image//staminaBar.tga");
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("crosshair", Color(1, 1, 1), 1, 1);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Courier.tga");
	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("textbox", Color(1, 1, 1), 1, 1);
	meshList[GEO_TEXTBOX]->textureID = LoadTGA("Image//textbox.tga");

	meshList[GEO_COAL] = MeshBuilder::GenerateOBJ("Coal", "OBJ//coal.obj");
	meshList[GEO_COAL]->textureID = LoadTGA("Image//coal.tga");

	meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//iron.obj");
	meshList[GEO_IRON]->textureID = LoadTGA("Image//iron.tga");

	meshList[GEO_COBALT] = MeshBuilder::GenerateOBJ("cobalt", "OBJ//cobalt.obj");
	meshList[GEO_COBALT]->textureID = LoadTGA("Image//cobalt.tga");

	meshList[GEO_ALIENPROBE] = MeshBuilder::GenerateOBJ("alienprobe", "OBJ//AlienProbe.obj");
	meshList[GEO_ALIENPROBE]->textureID = LoadTGA("Image//AlienProbe.tga");
	meshList[GEO_BEHOLDER] = MeshBuilder::GenerateOBJ("cylindertank", "OBJ//Beholder.obj");
	meshList[GEO_BEHOLDER]->textureID = LoadTGA("Image//Beholder.tga");

	meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND] = MeshBuilder::GenerateQuad("uibackground", Color(1, 1, 1), 1, 1);
	meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND]->textureID = LoadTGA("Image//uiBackground.tga");
	meshList[GEO_HEALTHBAR] = MeshBuilder::GenerateQuad("health", Color(1, 1, 1), 1, 1);
	meshList[GEO_HEALTHBAR]->textureID = LoadTGA("Image//healthBar.tga");
	meshList[GEO_OXYGENBAR] = MeshBuilder::GenerateQuad("oxygen", Color(1, 1, 1), 1, 1);
	meshList[GEO_OXYGENBAR]->textureID = LoadTGA("Image//oxygenBar.tga");
	meshList[GEO_STAMINABAR] = MeshBuilder::GenerateQuad("stamina", Color(1, 1, 1), 1, 1);
	meshList[GEO_STAMINABAR]->textureID = LoadTGA("Image//staminaBar.tga");

	//For UI assign(Make sure its after meshList)
	UIManager _UI(this);
	Scene::_UIManager = _UI;
	_player.scene_ = this;

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 2000.0f);
	projectionStack.LoadMatrix(projection);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(25, 19, -115);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(-25, 19, -115);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1.f;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	//ore
	_environmentManager.initRandPos(EnvironmentManager::ENVIRONMENT_TYPE::T_COAL, 10, camera.position, Vector3(-40, 0, -80), Vector3(0, 0, -30));
	for (int i = 0; i < EnvironmentManager::orePos.size(); i++)
		_gameObjectMananger.add(GameObjectManager::objectType::T_MINEABLE, new Vein(this, "ore", EnvironmentManager::orePos[i], Vein::ORE_TYPE::T_COAL, EnvironmentManager::oreRota[i]));
	_environmentManager.initRandPos(EnvironmentManager::ENVIRONMENT_TYPE::T_IRON, 10, camera.position, Vector3(-40, 0, -80), Vector3(0, 0, -30));
	for (int i = 0; i < EnvironmentManager::orePos.size(); i++)
		_gameObjectMananger.add(GameObjectManager::objectType::T_MINEABLE, new Vein(this, "ore", EnvironmentManager::orePos[i], Vein::ORE_TYPE::T_IRON, EnvironmentManager::oreRota[i]));
	_environmentManager.initRandPos(EnvironmentManager::ENVIRONMENT_TYPE::T_COBALT, 10, camera.position, Vector3(-40, 0, -80), Vector3(0, 0, -30));
	for (int i = 0; i < EnvironmentManager::orePos.size(); i++)
		_gameObjectMananger.add(GameObjectManager::objectType::T_MINEABLE, new Vein(this, "ore", EnvironmentManager::orePos[i], Vein::ORE_TYPE::T_COBALT, EnvironmentManager::oreRota[i]));


	//room wall stage 1
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(25, 20, -115), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(-25, 20, -115), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(25, 0, -115), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(-25, 0, -115), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallback", Vector3(50, 10, -115), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//back
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, -90), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, -90), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, -140), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, -140), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walldoor", Vector3(-50, 10, -115), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, -90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//front
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Walls(this, "door", Vector3(-49.9, 5, -115), Walls::WALL_TYPE::T_TUTORIALDOOR, Vector3(0, -90, 0), Vector3(7, 10, 7), Vector3(1, 5, 1)));

	 //room wall stage 2
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(25, 20, -55), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(-25, 20, -55), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(25, 0, -55), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(-25, 0, -55), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallback", Vector3(50, 10, -55), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//back
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, -30), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, -30), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, -80), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, -80), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walldoor", Vector3(-50, 10, -55), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, -90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//front
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Walls(this, "door", Vector3(-49.9, 5, -55), Walls::WALL_TYPE::T_TUTORIALDOOR, Vector3(0, -90, 0), Vector3(7, 10, 7), Vector3(1, 5, 1)));
	//room wall stage 3
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(25, 20, 5), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(-25, 20, 5), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(25, 0, 5), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(-25, 0, 5), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallback", Vector3(50, 10, 5), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//back
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, 30), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, 30), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, -20), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, -20), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walldoor", Vector3(-50, 10, 5), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, -90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//front
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Walls(this, "door", Vector3(-49.9, 5, 5), Walls::WALL_TYPE::T_TUTORIALDOOR, Vector3(0, -90, 0), Vector3(7, 10, 7), Vector3(1, 5, 1)));
	//room wall stage 4
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(25, 20, 65), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(-25, 20, 65), Walls::WALL_TYPE::T_TUTORIAL, Vector3(-90, 0, 0), Vector3(50, 50, 50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(25, 0, 65), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(-25, 0, 65), Walls::WALL_TYPE::T_TUTORIAL, Vector3(90, 0, -90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallback", Vector3(50, 10, 65), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//back
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, 90), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, 90), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 180, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(25, 10, 40), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(-25, 10, 40), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, 0, 0), Vector3(50, 20, 50), Vector3(25, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walldoor", Vector3(-50, 10, 65), Walls::WALL_TYPE::T_TUTORIAL, Vector3(0, -90, 0), Vector3(50, 20, 50), Vector3(0, 5, 25)));//front
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Walls(this, "door", Vector3(-49.9, 5, 65), Walls::WALL_TYPE::T_TUTORIALDOOR, Vector3(0, -90, 0), Vector3(7, 10, 7), Vector3(1, 5, 1)));


	//monster
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENEMY, new Monster(this, "AlienProbe", Vector3(-30,5,-10), Monster::MONSTER_TYPE::T_ENEMYPROBE,true));
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENEMY, new Monster(this, "AlienProbe", Vector3(-25, 5,20), Monster::MONSTER_TYPE::T_ENEMYPROBE, true));
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENEMY, new Monster(this, "Beholder", Vector3(-30, 5, -10), Monster::MONSTER_TYPE::T_ENEMYBEHOLDER, true));
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENEMY, new Monster(this, "Beholder", Vector3(-25, 5, 20), Monster::MONSTER_TYPE::T_ENEMYBEHOLDER, true));

	//upgrades
	//_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new WorkStation(this, "upgrader", Vector3(20, 5, -15), WorkStation::STATION_TYPE::T_UPGRADE, 0));

	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Weapon(this, "blaster", 999, 999));

}

void TScene::Update(double dt)
{
	Math::InitRNG();
	FPS = (float)(1.0f / dt);

	dt_ = dt;
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}

	if (Application::IsKeyPressed('8'))
	{
		lightsOn = false;
	}

	if (Application::IsKeyPressed('9'))
	{
		lightsOn = true;
	}

	if (Application::IsKeyPressed(VK_LSHIFT))
	{
		_player.getInstance()->isRunning = true;
	}
	if (Application::mouseClicked)
	{
		_gameObjectMananger.add(GameObjectManager::objectType::T_PLAYERPROJECTILE, new Bullet(this, "Bullet", Vector3(camera.position.x, camera.position.y, camera.position.z), Vector3(4, 4, 4)));
		Application::cantSpam = true;
	}

	dailycycle += 0.1 * dt;

	camera.Update(dt);
	camera.getCollider().updateColliderPos(camera.position);
	_gameObjectMananger.update(camera);
	_player.update(-dt);
	tsmthhappened += dt;

	if (bsmthhappend == true && tsmthhappened > 0.25)
	{
		bsmthhappend = false;
	}

	if (Application::IsKeyPressed('E') && bsmthhappend == false)
	{
		interact = true;
		bsmthhappend = true;
		tsmthhappened = 0;
	}

	//death go to mainmenu 
	if (_player.getInstance()->getCurrentHealth() < 1)
	{
		SceneManager::instance()->SetNextScene(7);
	}

	if (camera.position.z < -90) {
		stage = 1;
	}
	else if (camera.position.z < -30) {
		stage = 2;
		light[0].position.z = -55;
		light[1].position.z = -55;

	}
	else if (camera.position.z < 30) {
		stage = 3;
		light[0].position.z = 5;
		light[1].position.z = 5;

	}
	else if (camera.position.z < 90) {
		stage = 4;
		_gameObjectMananger.removeAll();
		SceneManager::instance()->SetNextScene(3);
	}

}

void TScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	// Initialize
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	//RenderMesh(meshList[GEO_AXES], false);
	//modelStack.PushMatrix();
	//modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	//RenderMesh(meshList[GEO_LIGHTBALL], false);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	RenderSkybox();	
	_gameObjectMananger.renderGameObjects();

	//FPS
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19));
	//player position
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("Position: " + std::to_string(camera.position.x) + " , " + std::to_string(camera.position.z), Color(1, 1, 0), 2, 0.5, 26));
	//inventory
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("Steel : " + std::to_string(player.inventory_.container.find("Steel")->second), Color(1, 1, 0), 2, 1, 14));
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("Iron : " + std::to_string(player.inventory_.container.find("Iron")->second), Color(1, 1, 0), 2, 1, 15));
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("Copper : " + std::to_string(player.inventory_.container.find("Copper")->second), Color(1, 1, 0), 2, 1, 16));
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("Silver : " + std::to_string(player.inventory_.container.find("Silver")->second), Color(1, 1, 0), 2, 1, 17));
	//_UIManager.renderTextOnScreen(UIManager::UI_Text("Gold : " + std::to_string(player.inventory_.container.find("Gold")->second), Color(1, 1, 0), 2, 1, 18));

	_UIManager.renderMeshOnScreen(meshList[GEO_TEXTBOX], 40, 54, 79, 10);

	if (stage == 1) {

		_UIManager.renderTextOnScreen(UIManager::UI_Text(tutorialtext[textoffset], Color(1, 0, 1), 3, 1, 19));

		if (textoffset != 3)
			_UIManager.renderTextOnScreen(UIManager::UI_Text(tutorialtext[0],  Color(1, 0, 1), 3, 19, 17));//next
		if (Application::IsKeyPressed(VK_SPACE) && textoffset < 3 && !bsmthhappend) {
			bsmthhappend = true;
			tsmthhappened = 0;
			textoffset++;
		}
	}

	if (stage == 2) {
		if (textoffset < 4)
			textoffset++;

		_UIManager.renderTextOnScreen(UIManager::UI_Text(tutorialtext[textoffset],  Color(1, 0, 1), 3, 1, 19));

		if (textoffset != 6)
			_UIManager.renderTextOnScreen(UIManager::UI_Text(tutorialtext[0],  Color(1, 0, 1), 3, 19, 17));//next
		if (Application::IsKeyPressed(VK_SPACE) && textoffset < 6 && !bsmthhappend) {
			bsmthhappend = true;
			tsmthhappened = 0;
			textoffset++;
		}
	}

	if (stage == 3) {
		if (textoffset < 7)
			textoffset++;

		_UIManager.renderTextOnScreen(UIManager::UI_Text(tutorialtext[textoffset],  Color(1, 0, 1), 3, 1, 19));

		if (textoffset != 8)
			_UIManager.renderTextOnScreen(UIManager::UI_Text(tutorialtext[0],  Color(1, 0, 1), 3, 19, 17));//next
		if (Application::IsKeyPressed(VK_SPACE) && textoffset < 8 && !bsmthhappend) {
			bsmthhappend = true;
			tsmthhappened = 0;
			textoffset++;
		}
	}


	_UIManager.renderMeshOnScreen(meshList[GEO_CROSSHAIR], 39.5, 27, 9, 10);

	//inventory
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Gold : " + std::to_string(_player.getInstance()->inventory_.container.find("Gold")->second), Color(1, 1, 0), 2, 1, 20)); //gold
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Silver : " + std::to_string(_player.getInstance()->inventory_.container.find("Silver")->second), Color(1, 1, 0), 2, 1, 19)); //silver
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Iron : " + std::to_string(_player.getInstance()->inventory_.container.find("Iron")->second), Color(1, 1, 0), 2, 1, 18)); //iron
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Steel : " + std::to_string(_player.getInstance()->inventory_.container.find("Steel")->second), Color(1, 1, 0), 2, 1, 17)); //steel
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Cobalt : " + std::to_string(_player.getInstance()->inventory_.container.find("Cobalt")->second), Color(1, 1, 0), 2, 1, 16)); //cobalt
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Copper : " + std::to_string(_player.getInstance()->inventory_.container.find("Copper")->second), Color(1, 1, 0), 2, 1, 15)); //copper
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Coal : " + std::to_string(_player.getInstance()->inventory_.container.find("Coal")->second), Color(1, 1, 0), 2, 1, 14)); //coal
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Scrap : " + std::to_string(_player.getInstance()->inventory_.container.find("Scrap")->second), Color(1, 1, 0), 2, 1, 13)); //scrap

	//Player
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Health : " + std::to_string(_player.getInstance()->getCurrentHealth()) + " / " + std::to_string(_player.getInstance()->getMaxHealth()), Color(1, 1, 0), 2, 0.5, 4));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Stamina : " + std::to_string(_player.getInstance()->getCurrentStamina()) + " / " + std::to_string(_player.getInstance()->getMaxStamina()), Color(1, 1, 0), 2, 0.5, 3));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Oxygen : " + std::to_string(_player.getInstance()->getOxygen()) + " / " + std::to_string(_player.getInstance()->getMaxOxygen()), Color(1, 1, 0), 2, 0.5, 2));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Ammo :" + std::to_string(Weapon::weaponAmmo_), Color(1, 1, 0), 2, 35, 2));

	//healthStaminaOxygen background
	_UIManager.renderMeshOnScreen(meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND], 40, 8, 30, 20);
	_UIManager.renderMeshOnScreen(meshList[GEO_HEALTHBAR], 40, 8, _player.getHealthBar(), 22);
	_UIManager.renderMeshOnScreen(meshList[GEO_STAMINABAR], 40, 6, _player.getStaminabar(), 22);
	_UIManager.renderMeshOnScreen(meshList[GEO_OXYGENBAR], 40, 4, _player.getOxygenbar(), 22);

}

void TScene::RenderSkybox()
{
	//space
	modelStack.PushMatrix();
	modelStack.Rotate(dailycycle, 0, 0, 1);
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 1000 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SUN], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, -1000 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_MOON], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1000 + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1000 + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, -1000 + camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, 1000 + camera.position.z);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void TScene::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
	_gameObjectMananger.removeAll();
}