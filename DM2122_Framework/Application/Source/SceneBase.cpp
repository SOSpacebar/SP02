#include "SceneBase.h"
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


SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	dailycycle = 0;
	tsmthhappened = 0;
	bsmthhappend = false;
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable Camera
	camera.Init(Vector3(-20, 6, -5), Vector3(0, 5, -5), Vector3(0, 1, 0));

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
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//snowGround.tga");
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.545098f, 0, 0), 0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("blade", Color(1, 0, 1), 16, 1, 1);
	meshList[GEO_ROOM] = MeshBuilder::GenerateQuad("Base", Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOM]->textureID = LoadTGA("Image//room.tga");
	meshList[GEO_ROOMDOOR] = MeshBuilder::GenerateQuad("Basedoor", Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOMDOOR]->textureID = LoadTGA("Image//roomwithdoor.tga");
	meshList[GEO_SPACE] = MeshBuilder::GenerateQuad("space", Color(1, 1, 1), 1, 1);
	meshList[GEO_SPACE]->textureID = LoadTGA("Image//Space.tga");
	meshList[GEO_SUN] = MeshBuilder::GenerateQuad("sun", Color(1, 1, 1), 1, 1);
	meshList[GEO_SUN]->textureID = LoadTGA("Image//SpaceSun.tga");
	meshList[GEO_MOON] = MeshBuilder::GenerateQuad("moon", Color(1, 1, 1), 1, 1);
	meshList[GEO_MOON]->textureID = LoadTGA("Image//SpaceMoon.tga");
	meshList[GEO_BLASTER] = MeshBuilder::GenerateOBJ("blaster", "OBJ//blaster.obj");
	meshList[GEO_BLASTER]->textureID = LoadTGA("Image//blasterblue.tga");
	meshList[GEO_LASERPROJ] = MeshBuilder::GenerateOBJ("laserProj", "OBJ//laserProjectile.obj");
	meshList[GEO_LASERPROJ]->textureID = LoadTGA("Image//laserProjectileRed.tga");

	meshList[GEO_CHEST] = MeshBuilder::GenerateOBJ("chest", "OBJ//Chest.obj");
	meshList[GEO_CHEST]->textureID = LoadTGA("Image//Chest.tga");
	meshList[GEO_ALIENPROBE] = MeshBuilder::GenerateOBJ("alienprobe", "OBJ//AlienProbe.obj");
	meshList[GEO_ALIENPROBE]->textureID = LoadTGA("Image//AlienProbe.tga");
	meshList[GEO_BEHOLDER] = MeshBuilder::GenerateOBJ("cylindertank", "OBJ//Beholder.obj");
	meshList[GEO_BEHOLDER]->textureID = LoadTGA("Image//Beholder.tga");
	meshList[GEO_STIMPAK] = MeshBuilder::GenerateOBJ("stimpak", "OBJ//Stimpak.obj");
	meshList[GEO_STIMPAK]->textureID = LoadTGA("Image//Stimpak.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//CandaraFont.tga");


	meshList[GEO_COAL] = MeshBuilder::GenerateOBJ("Coal", "OBJ//coal.obj");
	meshList[GEO_COAL]->textureID = LoadTGA("Image//coal.tga");

	meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//iron.obj");
	meshList[GEO_IRON]->textureID = LoadTGA("Image//iron.tga");

	meshList[GEO_COBALT] = MeshBuilder::GenerateOBJ("cobalt", "OBJ//cobalt.obj");
	meshList[GEO_COBALT]->textureID = LoadTGA("Image//cobalt.tga");

	//For UI assign(Make sure its after meshList)
	UIManager _UI(this);
	Scene::_UIManager = _UI;
	Application::cantSpam = true;


	Mtx44 projection;
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 2000.0f);
	projectionStack.LoadMatrix(projection);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 20, 0);
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
	light[1].position.Set(0, 0, 0);
	light[1].color.Set(1, 0, 1);
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

	//workplace
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new WorkStation(this, "trader", Vector3(20, 5, 0),WorkStation::STATION_TYPE::T_TRADE,0));
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new WorkStation(this, "furnace", Vector3(20, 5, 15), WorkStation::STATION_TYPE::T_FURNACE, 0));
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new WorkStation(this, "upgrader", Vector3(20, 5, -15), WorkStation::STATION_TYPE::T_UPGRADE, 0));

	//room wall
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walltop", Vector3(0, 20, 0), Walls::WALL_TYPE::T_PLAIN, Vector3(-90,0,0),Vector3(50,50,50), Vector3(0, 0, 0)));//top
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallbot", Vector3(0, 0.1, 0), Walls::WALL_TYPE::T_PLAIN, Vector3(90,0,-90), Vector3(50, 50, 50), Vector3(0, 0, 0)));//bot
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallback", Vector3(25, 10, 0), Walls::WALL_TYPE::T_PLAIN, Vector3(0,-90,0), Vector3(50, 20, 50),Vector3(0,5,50)));//back
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(0, 10, -25), Walls::WALL_TYPE::T_WINDOW, Vector3(0,180,0), Vector3(50, 20, 50), Vector3(50, 5, 0)));//side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "wallside", Vector3(0, 10, 25), Walls::WALL_TYPE::T_WINDOW, Vector3(0,0,0), Vector3(50, 20, 50), Vector3(50, 5, 0)));//other side
	_gameObjectMananger.add(GameObjectManager::objectType::T_WALL, new Walls(this, "walldoor", Vector3(-25, 10, 0), Walls::WALL_TYPE::T_DOOR, Vector3(0,-90,0), Vector3(50, 20, 50), Vector3(0, 5, 50)));//front






}

void SceneBase::Update(double dt)
{
	Math::InitRNG();
	FPS = (float)(1.0f / dt);

	dt_ = dt;
	time -= dt;

	tsmthhappened += dt;

	if (bsmthhappend == true && tsmthhappened > 1)
	{
		bsmthhappend = false;
	}


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

	if (Application::mouseClicked && Weapon::weaponAmmo_ != 0)
	{
		Weapon::weaponAmmo_--;
		_gameObjectMananger.add(GameObjectManager::objectType::T_PLAYERPROJECTILE, new Bullet(this, "Bullet", Vector3(camera.position.x, camera.position.y, camera.position.z), Vector3(4, 4, 4)));
		Application::cantSpam = true;
		std::cout << "Clicked" << std::endl;
	}

	if (Application::IsKeyPressed(VK_F1))
	{
		_gameObjectMananger.removeAll();
		SceneManager::instance()->SetNextScene(3);
	}

	dailycycle += 0.1 * dt;

	camera.Update(dt);
	camera.getCollider().updateColliderPos(camera.position);
	_gameObjectMananger.update(camera);
	_player.update(-dt);


	if (Application::IsKeyPressed('E') && bsmthhappend == false)
	{
		interact = true;
		bsmthhappend = true;
		tsmthhappened = 0;
	}

	if (Application::IsKeyPressed('Z') && bsmthhappend == false)
	{
		_player.inventory_.push("Iron", 1);//player picks up 1 element iron
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('X') && bsmthhappend == false)
	{
		_player.inventory_.push("Copper", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('C') && bsmthhappend == false)
	{
		_player.inventory_.push("Silver", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('V') && bsmthhappend == false)
	{
		_player.inventory_.push("Gold", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('B') && bsmthhappend == false)
	{
		_player.inventory_.push("Steel", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}

}

void SceneBase::Render()
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
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	RenderSkybox();


	//Ground
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1, 1000);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	_gameObjectMananger.renderGameObjects();

	_UIManager.renderTextOnScreen(UIManager::UI_Text("Time: " + std::to_string(time), Color(0, 1, 0), 3, .5f, 13));
	//FPS
	_UIManager.renderTextOnScreen(UIManager::UI_Text("FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19));
	//player position
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Position: " + std::to_string(camera.position.x) + " , " + std::to_string(camera.position.z), Color(1, 1, 0), 2, 0.5, 26));
	//inventory
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Steel : " + std::to_string(_player.inventory_.container.find("Steel")->second), Color(1, 1, 0), 2, 1, 14));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Iron : " + std::to_string(_player.inventory_.container.find("Iron")->second), Color(1, 1, 0), 2, 1, 15));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Copper : " + std::to_string(_player.inventory_.container.find("Copper")->second), Color(1, 1, 0), 2, 1, 16));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Silver : " + std::to_string(_player.inventory_.container.find("Silver")->second), Color(1, 1, 0), 2, 1, 17));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Gold : " + std::to_string(_player.inventory_.container.find("Gold")->second), Color(1, 1, 0), 2, 1, 18));

	_UIManager.renderTextOnScreen(UIManager::UI_Text("Interact : " + std::to_string(interact), Color(1, 1, 0), 2, 0.5, 27));

	//Player
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Health : " + std::to_string(_player.getCurrentHealth()) + " / " + std::to_string(_player.getMaxHealth()), Color(1, 1, 0), 2, 0.5, 5));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Stamina : " + std::to_string(_player.getCurrentStamina()) + " / " + std::to_string(_player.getCurrentStamina()), Color(1, 1, 0), 2, 0.5, 4));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Oxygen : " + std::to_string(_player.getOxygen()) + " / " + std::to_string(_player.getMaxOxygen()), Color(1, 1, 0), 2, 0.5, 3));

	//DebugCamPosition();
}

void SceneBase::RenderSkybox()
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

void SceneBase::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
