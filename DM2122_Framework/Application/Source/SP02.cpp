#include "SP02.h"
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

Player Scene::_player;
EnvironmentManager Scene::_environmentManager;
GameObjectManager Scene::_gameObjectMananger;
monsterManager Scene::_monsterManager;
UIManager Scene::_UIManager;

SP02::SP02()
{
}

SP02::~SP02()
{
}

void SP02::Init()
{
	//Player* player = Player::getInstance();
	dailycycle = 0;

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable Camera
	camera.Init(Vector3(20, 5, -5), Vector3(0, 5, -5), Vector3(0, 1, 0));

	// Init VBO here
	FPS = 0;
	lightsOn = true;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1);
	meshList[GEO_QUAD] = MeshBuilder::GenerateMultipleQuad("quad", Color(1, 1, 1), 1, 1,50);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Ground.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(.1f, .1f, .1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.545098f, 0, 0), 0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("blade", Color(1, 0, 1), 16, 1, 1);
	meshList[GEO_ROOM] = MeshBuilder::GenerateQuad("Base", Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOM]->textureID = LoadTGA("Image//room.tga");
	meshList[GEO_ROOMDOOR] = MeshBuilder::GenerateQuad("Basedoor",Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOMDOOR]->textureID = LoadTGA("Image//roomdoor.tga");
	meshList[GEO_SPACE] = MeshBuilder::GenerateQuad("space", Color(1, 1, 1), 1, 1);
	meshList[GEO_SPACE]->textureID = LoadTGA("Image//Space.tga");
	meshList[GEO_SUN] = MeshBuilder::GenerateQuad("sun", Color(1, 1, 1), 1, 1);
	meshList[GEO_SUN]->textureID = LoadTGA("Image//SpaceSun.tga");
	meshList[GEO_MOON] = MeshBuilder::GenerateQuad("moon", Color(1, 1, 1), 1, 1);
	meshList[GEO_MOON]->textureID = LoadTGA("Image//SpaceMoon.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1, 1);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//frontDark.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1, 1);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//backDark.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1, 1);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottomDark.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1, 1);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//topDark.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1, 1);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//leftDark.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1, 1);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//rightDark.tga");

	meshList[GEO_BLASTER] = MeshBuilder::GenerateOBJ("blaster", "OBJ//blaster.obj");
	meshList[GEO_BLASTER]->textureID = LoadTGA("Image//blasterblue.tga");
	meshList[GEO_BLASTER]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_BLASTER]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BLASTER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLASTER]->material.kShininess = 1.f;

	meshList[GEO_LASERPROJ] = MeshBuilder::GenerateOBJ("laserProj", "OBJ//laserProjectile.obj");
	meshList[GEO_LASERPROJ]->textureID = LoadTGA("Image//laserProjectileRed.tga");

	meshList[GEO_CHEST] = MeshBuilder::GenerateOBJ("chest", "OBJ//Chest.obj");
	meshList[GEO_CHEST]->textureID = LoadTGA("Image//Chest.tga");
	meshList[GEO_ALIENPROBE] = MeshBuilder::GenerateOBJ("alienprobe", "OBJ//AlienProbe.obj");
	meshList[GEO_ALIENPROBE]->textureID = LoadTGA("Image//AlienProbe.tga");
	meshList[GEO_ALIENPROBE]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_ALIENPROBE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_ALIENPROBE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_ALIENPROBE]->material.kShininess = 1.f;

	meshList[GEO_BEHOLDER] = MeshBuilder::GenerateOBJ("cylindertank", "OBJ//Beholder.obj");
	meshList[GEO_BEHOLDER]->textureID = LoadTGA("Image//Beholder.tga");
	meshList[GEO_BEHOLDER]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_BEHOLDER]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BEHOLDER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BEHOLDER]->material.kShininess = 1.f;

	meshList[GEO_STIMPAK] = MeshBuilder::GenerateOBJ("stimpak", "OBJ//Stimpak.obj");
	meshList[GEO_STIMPAK]->textureID = LoadTGA("Image//Stimpak.tga");

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


	meshList[GEO_COAL] = MeshBuilder::GenerateOBJ("Coal", "OBJ//coal.obj");
	meshList[GEO_COAL]->textureID = LoadTGA("Image//coal.tga");
	meshList[GEO_COAL]->material.kAmbient.Set(.1f, .1f, .1f);
	meshList[GEO_COAL]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COAL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COAL]->material.kShininess = 1.f;

	meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//iron.obj");
	meshList[GEO_IRON]->textureID = LoadTGA("Image//iron.tga");
	meshList[GEO_IRON]->material.kAmbient.Set(.1f, .1f, .1f);
	meshList[GEO_IRON]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_IRON]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_IRON]->material.kShininess = 1.f;

	meshList[GEO_COBALT] = MeshBuilder::GenerateOBJ("cobalt", "OBJ//cobalt.obj");
	meshList[GEO_COBALT]->textureID = LoadTGA("Image//cobalt.tga");
	meshList[GEO_COBALT]->material.kAmbient.Set(.1f, .1f, .1f);
	meshList[GEO_COBALT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COBALT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COBALT]->material.kShininess = 1.f;

	//For UI assign(Make sure its after meshList)
	UIManager _UI(this);
	Scene::_UIManager = _UI;

	//Assign scene to player.
	_player.scene_ = this;
	Application::cantSpam = true;


	Mtx44 projection;
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 2000.0f);
	projectionStack.LoadMatrix(projection);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.3;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1.0f;
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

	_environmentManager.initRandPos(EnvironmentManager::ENVIRONMENT_TYPE::T_COAL,30, camera.position,Vector3(-75,0,-75),Vector3(75,0,75));
	for (int i = 0; i < EnvironmentManager::orePos.size(); i++)
		_gameObjectMananger.add(GameObjectManager::objectType::T_MINEABLE, new Vein(this, "ore", EnvironmentManager::orePos[i],Vein::ORE_TYPE::T_COAL, EnvironmentManager::oreRota[i]));

	_environmentManager.initRandPos(EnvironmentManager::ENVIRONMENT_TYPE::T_IRON,20, camera.position, Vector3(-75, 0, -75), Vector3(75, 0, 75));
	for (int i = 0; i < EnvironmentManager::orePos.size(); i++)
		_gameObjectMananger.add(GameObjectManager::objectType::T_MINEABLE, new Vein(this, "ore", EnvironmentManager::orePos[i], Vein::ORE_TYPE::T_IRON, EnvironmentManager::oreRota[i]));

	_environmentManager.initRandPos(EnvironmentManager::ENVIRONMENT_TYPE::T_COBALT,10,camera.position, Vector3(-75, 0, -75), Vector3(75, 0, 75));
	for (int i = 0; i < EnvironmentManager::orePos.size(); i++)
		_gameObjectMananger.add(GameObjectManager::objectType::T_MINEABLE, new Vein(this, "ore", EnvironmentManager::orePos[i], Vein::ORE_TYPE::T_COBALT, EnvironmentManager::oreRota[i]));

	//monsters
	_monsterManager.initRandPos(monsterManager::MONSTER_TYPE::T_ENEMYPROBE, 100, camera.position, Vector3(-150, 0, 150), Vector3(150, 0, 0));
	for (int i = 0; i < count * 0; i++)
	{
		_gameObjectMananger.add(GameObjectManager::objectType::T_ENEMY, new Monster(this, "AlienProbe", monsterManager::monsterPos[i], Monster::MONSTER_TYPE::T_ENEMYPROBE));
	}
	_monsterManager.initRandPos(monsterManager::MONSTER_TYPE::T_ENEMYPROBE, 100, camera.position, Vector3(-150, 0, 150), Vector3(150, 0, 0));
	for (int i = 0; i < count * 5; i++)
	{
		_gameObjectMananger.add(GameObjectManager::objectType::T_ENEMY, new Monster(this, "Beholder", monsterManager::monsterPos[i], Monster::MONSTER_TYPE::T_ENEMYBEHOLDER));
	}

	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Weapon(this, "blaster", 10, 10));


	_player.getInstance();
}

void SP02::Update(double dt)
{
	Math::InitRNG();
	FPS = (float)(1.0f / dt);
	
	dt_ = dt;

	if (monsterCount <= 0)
		time -= dt;

	rotateStimpak += (float)(20 * dt);
	static const float LSPEED = 10.f; 

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
/*
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);
*/

	if (Application::mouseClicked && Weapon::weaponAmmo_ !=0)
	{
		Weapon::weaponAmmo_--;
		_gameObjectMananger.add(GameObjectManager::objectType::T_PLAYERPROJECTILE, new Bullet(this, "Bullet", Vector3(camera.position.x, camera.position.y, camera.position.z), Vector3(4, 4, 4)));
		Application::cantSpam = true;
	}
	if (Weapon::weaponAmmo_ == 0) //reload
	{
		Application::mouseClicked = false;
		reloadTime += (float)(1 * dt);
		if (reloadTime > 2)
		{
			Weapon::weaponAmmo_ = 10;
			Application::mouseClicked = true;
			reloadTime = 0;
		}
	}
		
	if (Application::IsKeyPressed(VK_F1))
	{
		SceneManager::instance()->SetNextScene(0);
	}

	dailycycle += 0.1 * dt;

	camera.Update(dt);
	camera.getCollider().updateColliderPos(camera.position);
	_gameObjectMananger.update(camera);
	_player.update(-dt);


	if (Application::IsKeyPressed('E'))
	{
		interact = true;
	}

	if (Application::IsKeyPressed(VK_LSHIFT))
	{
		_player.getInstance()->isRunning = true;
	}

	if (time <= 0)
	{
		std::cout << monsterCount;
		SceneManager::instance()->SetNextScene(3);
		time = 10;
		if (count <5)
		{
			count++;
		}
	}
//death
	if (_player.getInstance()->getCurrentHealth() < 1)
	{
		SceneManager::instance()->SetNextScene(5);
	}
}

void SP02::Render()
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

	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PushMatrix();
	//modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	//RenderMesh(meshList[GEO_LIGHTBALL], false);
	//modelStack.PopMatrix();

	RenderSkybox();
	
	//Ground
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1, 1000);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	_gameObjectMananger.renderGameObjects();

	_UIManager.renderTextOnScreen(UIManager::UI_Text("Time: " + std::to_string(time), Color(0, 1, 0), 3, .5f, 16));
	//FPS
	_UIManager.renderTextOnScreen(UIManager::UI_Text("FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19));
	//player position
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Position: " + std::to_string(camera.position.x) + " , " + std::to_string(camera.position.z), Color(1, 1, 0), 2, 0.5, 26));
	//inventory
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Gold		: " + std::to_string(_player.getInstance()->inventory_.container.find("Gold")->second), Color(1, 1, 0), 2, 1, 20)); //gold
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Silver	: " + std::to_string(_player.getInstance()->inventory_.container.find("Silver")->second), Color(1, 1, 0), 2, 1, 19)); //silver
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Iron		: " + std::to_string(_player.getInstance()->inventory_.container.find("Iron")->second), Color(1, 1, 0), 2, 1, 18)); //iron
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Steel		: " + std::to_string(_player.getInstance()->inventory_.container.find("Steel")->second), Color(1, 1, 0), 2, 1, 17)); //steel
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Cobalt	: " + std::to_string(_player.getInstance()->inventory_.container.find("Cobalt")->second), Color(1, 1, 0), 2, 1, 16)); //cobalt
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Copper	: " + std::to_string(_player.getInstance()->inventory_.container.find("Copper")->second), Color(1, 1, 0), 2, 1, 15)); //copper
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Coal		: " + std::to_string(_player.getInstance()->inventory_.container.find("Coal")->second), Color(1, 1, 0), 2, 1, 14)); //coal
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Scrap		: " + std::to_string(_player.getInstance()->inventory_.container.find("Scrap")->second), Color(1, 1, 0), 2, 1, 13)); //scrap

	_UIManager.renderTextOnScreen(UIManager::UI_Text("Interact : " + std::to_string(interact), Color(1, 1, 0), 2, 0.5, 27));
	
	//Player
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Health  : " + std::to_string(_player.getInstance()->getCurrentHealth()) + " / " + std::to_string(_player.getInstance()->getMaxHealth()), Color(1, 1, 0), 2, 0.5, 4));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Stamina : " + std::to_string(_player.getInstance()->getCurrentStamina()) + " / " + std::to_string(_player.getInstance()->getMaxStamina()), Color(1, 1, 0), 2, 0.5, 3));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Oxygen  : " + std::to_string(_player.getInstance()->getOxygen()) + " / " + std::to_string(_player.getInstance()->getMaxOxygen()), Color(1, 1, 0), 2, 0.5, 2));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Ammo :" + std::to_string(Weapon::weaponAmmo_), Color(1, 1, 0), 2, 35, 2));

	//healthStaminaOxygen background
	_UIManager.renderMeshOnScreen(meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND], 40, 8, 30, 20);
	_UIManager.renderMeshOnScreen(meshList[GEO_HEALTHBAR], 40, 8, _player.getInstance()->getHealthBar(), 22);
	_UIManager.renderMeshOnScreen(meshList[GEO_STAMINABAR], 40, 6, _player.getInstance()->getStaminabar(), 22);
	_UIManager.renderMeshOnScreen(meshList[GEO_OXYGENBAR], 40, 4, _player.getInstance()->getOxygenbar(), 22);

	_UIManager.renderMeshOnScreen(meshList[GEO_CROSSHAIR], 39.8, 27, 9, 12);

	//DebugCamPosition();
}

void SP02::RenderSkybox()
{
	//space
	//top
	modelStack.PushMatrix();
	modelStack.Rotate(dailycycle, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 1000 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SUN], false);
	modelStack.PopMatrix();

	//btm
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, -1000 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_MOON], false);
	modelStack.PopMatrix();

	//front
	modelStack.PushMatrix();
	modelStack.Translate(1000 + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();

	//back
	modelStack.PushMatrix();
	modelStack.Translate(-1000 + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();

	//right
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, -1000 + camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();

	//left
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, 1000 + camera.position.z);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_SPACE], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//background
	//front
	modelStack.PushMatrix();
	modelStack.Translate(499 , 100, 0 );
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 200, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//back
	modelStack.PushMatrix();
	modelStack.Translate(-499, 100, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 200, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//right
	modelStack.PushMatrix();
	modelStack.Translate(0, 100, -499);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 200, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//left
	modelStack.PushMatrix();
	modelStack.Translate(0 , 100, 499);
	modelStack.Scale(1000, 200, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
}

void SP02::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
	_gameObjectMananger.removeAll();
}
