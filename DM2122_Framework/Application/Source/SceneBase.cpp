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
	//upgrade
	WDcount = 0;
	WAcount = 0;
	OxyCount = 0;
	StaCount = 0;
	HPCount = 0;
	//upgrade setter var
	OX = 0;
	HP = 0;
	ST = 0;
	 //trade
	 Goldcnt=0;//1
	 Silvercnt=0;//2
	 Ironcnt=0;//3
	 Steelcnt=0;//4
	 Cobaltcnt=0;//5
	 Coppercnt=0;//6
	 Coalcnt=0;//7
	 //trade cost
	 SilverCOST=0;//2
	 IronCOST=0;//3
	 SteelCOST=0;//4
	 CobaltCOST=0;//5
	 CopperCOST=0;//6
	 GoldCOST=0;//7
	 //Furnace
	 Scrapcnt = 0;
	
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
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.5, 0.5, 1), 1, 1);
	//meshList[GEO_QUAD]->textureID = LoadTGA("Image//snowGround.tga");
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.545098f, 0, 0), 0.5f, 0.5f, 0.5f);
	meshList[GEO_ROOM] = MeshBuilder::GenerateQuad("Base", Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOM]->textureID = LoadTGA("Image//room.tga");
	meshList[GEO_ROOM]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_ROOM]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_ROOM]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_ROOM]->material.kShininess = 3.f;
	meshList[GEO_ROOMDOOR] = MeshBuilder::GenerateQuad("Basedoor", Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOMDOOR]->textureID = LoadTGA("Image//roomwithdoor.tga");
	meshList[GEO_ROOMDOOR]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_ROOMDOOR]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_ROOMDOOR]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_ROOMDOOR]->material.kShininess = 3.f;
	meshList[GEO_ROOMWINDOW] = MeshBuilder::GenerateQuad("Basewindow", Color(1, 1, 1), 1, 1);
	meshList[GEO_ROOMWINDOW]->textureID = LoadTGA("Image//Window.tga");
	meshList[GEO_ROOMWINDOW]->material.kAmbient.Set(.5f, .5f, .5f);
	meshList[GEO_ROOMWINDOW]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_ROOMWINDOW]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_ROOMWINDOW]->material.kShininess = 3.f;
	meshList[GEO_SPACE] = MeshBuilder::GenerateQuad("space", Color(1, 1, 1), 1, 1);
	meshList[GEO_SPACE]->textureID = LoadTGA("Image//Space.tga");
	meshList[GEO_SUN] = MeshBuilder::GenerateQuad("sun", Color(1, 1, 1), 1, 1);
	meshList[GEO_SUN]->textureID = LoadTGA("Image//SpaceSun.tga");
	meshList[GEO_MOON] = MeshBuilder::GenerateQuad("moon", Color(1, 1, 1), 1, 1);
	meshList[GEO_MOON]->textureID = LoadTGA("Image//SpaceMoon.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Courier.tga");

	meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND] = MeshBuilder::GenerateQuad("uibackground", Color(1, 1, 1), 1, 1);
	meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND]->textureID = LoadTGA("Image//uiBackground.tga");
	meshList[GEO_HEALTHBAR] = MeshBuilder::GenerateQuad("health", Color(1, 1, 1), 1, 1);
	meshList[GEO_HEALTHBAR]->textureID = LoadTGA("Image//healthBar.tga");
	meshList[GEO_OXYGENBAR] = MeshBuilder::GenerateQuad("oxygen", Color(1, 1, 1), 1, 1);
	meshList[GEO_OXYGENBAR]->textureID = LoadTGA("Image//oxygenBar.tga");
	meshList[GEO_STAMINABAR] = MeshBuilder::GenerateQuad("stamina", Color(1, 1, 1), 1, 1);
	meshList[GEO_STAMINABAR]->textureID = LoadTGA("Image//staminaBar.tga");

	meshList[GEO_UPGRADEUI] = MeshBuilder::GenerateQuad("upgradeui", Color(0.5, 0.5, 1), 1, 1);
	meshList[GEO_UPGRADEUI]->textureID = LoadTGA("Image//upgraderUI.tga");
	meshList[GEO_TRADINGUI] = MeshBuilder::GenerateQuad("tradingui", Color(0.5, 0.5, 1), 1, 1);
	meshList[GEO_TRADINGUI]->textureID = LoadTGA("Image//tradingUI.tga");
	meshList[GEO_FURNACEUI] = MeshBuilder::GenerateQuad("furnaceui", Color(0.5, 0.5, 1), 1, 1);
	meshList[GEO_FURNACEUI]->textureID = LoadTGA("Image//furnaceUI.tga");

	meshList[GEO_UPGRADER] = MeshBuilder::GenerateOBJ("upgrader", "OBJ//upgradeRobot.obj");
	meshList[GEO_UPGRADER]->textureID = LoadTGA("Image//upgradeRobot.tga");
	meshList[GEO_TRADER] = MeshBuilder::GenerateOBJ("trader", "OBJ//traderRobot.obj");
	meshList[GEO_TRADER]->textureID = LoadTGA("Image//traderRobot.tga");
	meshList[GEO_FURNACE] = MeshBuilder::GenerateOBJ("Furnace", "OBJ//traderRobot.obj");
	meshList[GEO_FURNACE]->textureID = LoadTGA("Image//furnace.tga");


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
	_player.getInstance()->scene_ = this;


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

	//light[1].type = Light::LIGHT_POINT;
	//light[1].position.Set(0, 0, 0);
	//light[1].color.Set(1, 0, 1);
	//light[1].power = 1.0f;
	//light[1].kC = 1.f;
	//light[1].kL = 0.01f;
	//light[1].kQ = 0.001f;
	//light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	//light[1].cosInner = cos(Math::DegreeToRadian(30));
	//light[1].exponent = 3.f;
	//light[1].spotDirection.Set(0.f, 1.f, 0.f);

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

	//m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	//m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	//m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	//m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	//m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	//m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	//m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	//m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	//m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	//m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	//m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

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

	//glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	//glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	//glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	//glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	//glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	//glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	//glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	//glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	//glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	//workplace
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new WorkStation(this, "trader", Vector3(20, 5, 0), WorkStation::STATION_TYPE::T_TRADE, 0));
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
	FPS = (float)(1.0f / dt);

	tsmthhappened += dt;

	if (bsmthhappend == true && tsmthhappened > 0.5)
	{
		bsmthhappend = false;
	}

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

	if (Application::IsKeyPressed('8'))
	{
		lightsOn = false;
	}

	if (Application::IsKeyPressed('9'))
	{
		lightsOn = true;
	}

	if (Application::IsKeyPressed('F'))
	{
		_gameObjectMananger.removeAll();
		SceneManager::instance()->SetNextScene(4);
	}

	dailycycle += 0.1 * dt;

	if (!WorkStation::open && !WorkStation::Topen)
	{
		glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		camera.Update(dt);
		camera.getCollider().updateColliderPos(camera.position);
		_player.getInstance()->update(-dt);
	}
	_gameObjectMananger.update(camera);


	if (Application::IsKeyPressed('E') && bsmthhappend == false)
	{
		interact = true;
		bsmthhappend = true;
		tsmthhappened = 0;
	}
					
	if (Application::IsKeyPressed(VK_LSHIFT))
	{
		_player.getInstance()->isRunning = true;
	}
					
	if (Application::IsKeyPressed('Z') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Coal", 1);
					
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('X') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Iron", 1);//player picks up 1 element iron
							bsmthhappend = true;
							tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('C') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Cobalt", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('V') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Gold", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('B') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Steel", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('N') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Silver", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('M') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Copper", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}
	if (Application::IsKeyPressed('L') && bsmthhappend == false)
	{
		_player.getInstance()->inventory_.push("Scrap", 1);
		bsmthhappend = true;
		tsmthhappened = 0;
	}

			if (WorkStation::Uopen)
			{
				Vector3 MousePos(Application::MouseXPos_, Application::MouseYPos_, 0);
				//DECREASE
				//bottom left point
				//top right point
				//interaction bool
				//count condition
				if (Application::mouseClicked &&
					MousePos.x > 430 && 
					MousePos.y > 140 && 
					MousePos.x < 460 &&
					MousePos.y < 160 &&
					bsmthhappend == false &&
					WDcount> 0)
				{
					WDcount--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//y+30
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 180 &&
					MousePos.x < 460 &&
					MousePos.y < 200 &&
					bsmthhappend == false &&
					WAcount >0)
				{
					WAcount--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
			
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 230 &&
					MousePos.x < 460 &&
					MousePos.y < 250 &&
					bsmthhappend == false &&
			
					HPCount > 0)
				{
					HPCount--;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 290 &&
					MousePos.x < 460 && 
					MousePos.y < 310 && 
					bsmthhappend == false &&
					OxyCount > 0)
				{
					OxyCount--;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				if (Application::mouseClicked &&
					MousePos.x > 430 && 
					MousePos.y > 330 && 
					MousePos.x < 460 &&
					MousePos.y < 350 && 
					bsmthhappend == false &&
					StaCount>0)
				{
					StaCount--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//ADDING
			    if (Application::mouseClicked 
					&& MousePos.x > 490 &&
					MousePos.y > 140 &&
					MousePos.x < 520 &&
					MousePos.y < 160 && 
					bsmthhappend == false &&
					WDcount < 9)
				{
					WDcount++;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
			
				if (Application::mouseClicked &&
					MousePos.x > 490 && 
					MousePos.y > 180 && 
					MousePos.x < 520 &&
					MousePos.y < 200 && 
					bsmthhappend == false && 
					
					WAcount < 9)
				{
					WAcount++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				if (Application::mouseClicked && 
					MousePos.x > 490 && 
					MousePos.y > 230 &&
					MousePos.x < 520 &&
					MousePos.y < 250 && 
					bsmthhappend == false &&
					
					HPCount < 9)
				{
					HPCount++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 290 &&
					MousePos.x < 520 && 
					MousePos.y < 310 && 
					bsmthhappend == false && 
					
					OxyCount < 9)
				{
					OxyCount++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				if (Application::mouseClicked && 
					MousePos.x > 490 &&
					MousePos.y > 330 && 
					MousePos.x < 520 &&
					MousePos.y < 350 &&
					bsmthhappend == false &&
					
					StaCount < 9)
				{
					StaCount++;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
			
			
				//cost update
				IronCost = WDcount + OxyCount + StaCount;
				CobaltCost = WAcount + HPCount;
				OX = (OxyCount * 50) + (_player.getInstance()->getMaxOxygen());
				HP = (HPCount * 50) + (_player.getInstance()->getMaxHealth());
				ST = (StaCount * 50) + (_player.getInstance()->getMaxStamina());
			
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 480 && 
					MousePos.x < 550 &&
					MousePos.y < 500 && 
					bsmthhappend == false)
				{
					std::cout << "confirm" << std::endl;
					bsmthhappend = true;
					tsmthhappened = 0;
			
					if ((IronCost <= (_player.getInstance()->inventory_.container.find("Iron")->second)) && (CobaltCost <= (_player.getInstance()->inventory_.container.find("Cobalt")->second)))
					{
						_player.getInstance()->inventory_.upgrade("Iron", IronCost);
						_player.getInstance()->inventory_.upgrade("Cobalt", CobaltCost);
						_player.getInstance()->setplayerstat(HP, OX, ST);
					}
			
				}
			}
			if (WorkStation::Topen)
			{
				Vector3 MousePos(Application::MouseXPos_, Application::MouseYPos_, 0);
				//DECREASE
				//bottom left point
				//top right point
				//interaction bool
				//count condition
				//1
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 170 &&
					MousePos.x < 460 &&
					MousePos.y < 190 &&
					bsmthhappend == false &&
					
					Goldcnt> 0)
				{
					Goldcnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//y+30
				//2
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 210 &&
					MousePos.x < 460 &&
					MousePos.y < 230 &&
					bsmthhappend == false &&
			
					Silvercnt >0)
				{
					Silvercnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//3
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 250 &&
					MousePos.x < 460 &&
					MousePos.y < 270 &&
					bsmthhappend == false &&
			
					Ironcnt >0)
				{
					Ironcnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//4
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 300 &&
					MousePos.x < 460 &&
					MousePos.y < 320 &&
					bsmthhappend == false &&
			
					Steelcnt > 0)
				{
					Steelcnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				//5
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 340 &&
					MousePos.x < 460 &&
					MousePos.y < 360 &&
					bsmthhappend == false &&
			
					Cobaltcnt > 0)
				{
					Cobaltcnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				//6
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 390 &&
					MousePos.x < 460 &&
					MousePos.y < 410 &&
					bsmthhappend == false &&
			
					Coppercnt>0)
				{
					Coppercnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//7
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 430 &&
					MousePos.x < 460 &&
					MousePos.y < 450 &&
					bsmthhappend == false &&
			
					Coalcnt>0)
				{
					Coalcnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//ADDING
				//x+60
				//1
				if (Application::mouseClicked
					&& MousePos.x > 490 &&
					MousePos.y > 170 &&
					MousePos.x < 520 &&
					MousePos.y < 190 &&
					bsmthhappend == false &&
			
					Goldcnt < 9)
				{
					Goldcnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				//2
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 210 &&
					MousePos.x < 520 &&
					MousePos.y < 230 &&
					bsmthhappend == false &&
			
					Silvercnt < 9)
				{
					Silvercnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				//3
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 250 &&
					MousePos.x < 520 &&
					MousePos.y < 270 &&
					bsmthhappend == false &&
			
					Ironcnt < 9)
				{
					Ironcnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//4
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 300 &&
					MousePos.x < 520 &&
					MousePos.y < 320 &&
					bsmthhappend == false &&
			
					Steelcnt < 9)
				{
					Steelcnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				//5
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 340 &&
					MousePos.x < 520 &&
					MousePos.y < 360 &&
					bsmthhappend == false &&
			
					Cobaltcnt < 9)
				{
					Cobaltcnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				//6
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 390 &&
					MousePos.x < 520 &&
					MousePos.y < 410 &&
					bsmthhappend == false &&
			
					Coppercnt < 9)
				{
					Coppercnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//7
				if (Application::mouseClicked &&
					MousePos.x > 490 &&
					MousePos.y > 430 &&
					MousePos.x < 520 &&
					MousePos.y < 450 &&
					bsmthhappend == false &&
			
					Coalcnt < 9)
				{
					Coalcnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
			
				GoldCOST=Goldcnt*200;//1
				SilverCOST=Silvercnt*100;//2
				IronCOST=Ironcnt*75;//3
				SteelCOST=Steelcnt*50;//4
				CobaltCOST=Cobaltcnt*20;//5
				CopperCOST=Coppercnt*5;//6
				
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 480 &&
					MousePos.x < 550 &&
					MousePos.y < 500 &&
					bsmthhappend == false)
				{
					std::cout << "confirm" << std::endl;
					bsmthhappend = true;
					tsmthhappened = 0;
			
					if (GoldCOST <= (_player.getInstance()->inventory_.container.find("Silver")->second) &&
						SilverCOST <= (_player.getInstance()->inventory_.container.find("Iron")->second) &&
						IronCOST <= (_player.getInstance()->inventory_.container.find("Steel")->second) &&
						SteelCOST <= (_player.getInstance()->inventory_.container.find("Cobalt")->second) &&
						CobaltCOST <= (_player.getInstance()->inventory_.container.find("Copper")->second) &&
						CopperCOST <= (_player.getInstance()->inventory_.container.find("Coal")->second))
					{
						_player.getInstance()->inventory_.trade("Copper", "Coal", Coppercnt, CopperCOST);
						_player.getInstance()->inventory_.trade("Cobalt", "Copper", Cobaltcnt, CobaltCOST);
						_player.getInstance()->inventory_.trade("Steel", "Cobalt", Steelcnt, SteelCOST);
						_player.getInstance()->inventory_.trade("Iron", "Steel", Ironcnt, IronCOST);
						_player.getInstance()->inventory_.trade("Silver", "Iron", Silvercnt, SilverCOST);
						_player.getInstance()->inventory_.trade("Gold", "Silver", Goldcnt, GoldCOST);
						
					}
						
				}
			}
			if (WorkStation::Fopen)
			{
				Vector3 MousePos(Application::MouseXPos_, Application::MouseYPos_, 0);
				//DECREASE
				//bottom left point
				//top right point
				//interaction bool
				//count condition
				//1
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 140 &&
					MousePos.x < 460 &&
					MousePos.y < 160 &&
					bsmthhappend == false &&
			
					Scrapcnt> 0)
				{
					Scrapcnt--;
					bsmthhappend = true;
					tsmthhappened = 0;
				}
				//Add
				if (Application::mouseClicked
					&& MousePos.x > 490 &&
					MousePos.y > 140 &&
					MousePos.x < 520 &&
					MousePos.y < 160 &&
					bsmthhappend == false &&
			
					Scrapcnt < 9)
				{
					Scrapcnt++;
					bsmthhappend = true;
					tsmthhappened = 0;
			
				}
				if (Application::mouseClicked &&
					MousePos.x > 430 &&
					MousePos.y > 500 &&
					MousePos.x < 550 &&
					MousePos.y < 520 &&
					bsmthhappend == false)
				{
					std::cout << "confirm" << std::endl;
					bsmthhappend = true;
					tsmthhappened = 0;
			
					if (Scrapcnt <= (_player.getInstance()->inventory_.container.find("Scrap")->second))
					{
						_player.getInstance()->inventory_.melt("Scrap", Scrapcnt, dt);
					}
				}
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

	_gameObjectMananger.renderGameObjects();

	if (camera.position.x > -25 && camera.position.x < -15 && camera.position.z <= 0 && camera.position.z >= -10)
	{
		_UIManager.renderTextOnScreen(UIManager::UI_Text("PRESS F TO OPEN", Color(1, 0, 0), 2, 30, 2));
	}

	//FPS
	_UIManager.renderTextOnScreen(UIManager::UI_Text("FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19));
	
	//inventory
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Gold		: " + std::to_string(_player.inventory_.container.find("Gold")->second), Color(1, 1, 0), 2, 1, 20)); //gold
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Silver	: " + std::to_string(_player.inventory_.container.find("Silver")->second), Color(1, 1, 0), 2, 1, 19)); //silver
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Iron		: " + std::to_string(_player.inventory_.container.find("Iron")->second), Color(1, 1, 0), 2, 1, 18)); //iron
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Steel		: " + std::to_string(_player.inventory_.container.find("Steel")->second), Color(1, 1, 0), 2, 1, 17)); //steel
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Cobalt	: " + std::to_string(_player.inventory_.container.find("Cobalt")->second), Color(1, 1, 0), 2, 1, 16)); //cobalt
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Copper	: " + std::to_string(_player.inventory_.container.find("Copper")->second), Color(1, 1, 0), 2, 1, 15)); //copper
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Coal		: " + std::to_string(_player.inventory_.container.find("Coal")->second), Color(1, 1, 0), 2, 1, 14)); //coal
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Scrap		: " + std::to_string(_player.inventory_.container.find("Scrap")->second), Color(1, 1, 0), 2, 1, 13)); //scrap

	_UIManager.renderTextOnScreen(UIManager::UI_Text("Interact : " + std::to_string(interact), Color(1, 1, 0), 2, 0.5, 27));

	//Player
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Health : " + std::to_string(_player.getInstance()->getCurrentHealth()) + " / " + std::to_string(_player.getInstance()->getMaxHealth()), Color(1, 1, 0), 2, 0.5, 4));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Stamina : " + std::to_string(_player.getInstance()->getCurrentStamina()) + " / " + std::to_string(_player.getInstance()->getMaxStamina()), Color(1, 1, 0), 2, 0.5, 3));
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Oxygen : " + std::to_string(_player.getInstance()->getOxygen()) + " / " + std::to_string(_player.getInstance()->getMaxOxygen()), Color(1, 1, 0), 2, 0.5, 2));

	//healthStaminaOxygen background
	_UIManager.renderMeshOnScreen(meshList[GEO_HEALTHSTAMINAOXYGENBACKGROUND], 40, 8, 30, 20);
	_UIManager.renderMeshOnScreen(meshList[GEO_HEALTHBAR], 40, 8, _player.getInstance()->getHealthBar(), 22);
	_UIManager.renderMeshOnScreen(meshList[GEO_STAMINABAR], 40, 6, _player.getInstance()->getStaminabar(), 22);
	_UIManager.renderMeshOnScreen(meshList[GEO_OXYGENBAR], 40, 4, _player.getInstance()->getOxygenbar(), 22);

	//machine info
	if (WorkStation::open && WorkStation::Topen)
	{
		glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		_UIManager.renderMeshOnScreen(meshList[GEO_TRADINGUI], 40, 30, 50, 50);

		//buy
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Goldcnt) + " +", Color(0, 0, 0), 3, 15, 14));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Silvercnt) + " +", Color(0, 0, 0), 3, 15, 12.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Ironcnt) + " +", Color(0, 0, 0), 3, 15, 11));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Steelcnt) + " +", Color(0, 0, 0), 3, 15, 9.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Cobaltcnt) + " +", Color(0, 0, 0), 3, 15, 8));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Coppercnt) + " +", Color(0, 0, 0), 3, 15, 6.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Coalcnt) + " +", Color(0, 0, 0), 3, 15, 5));
		//cost
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(GoldCOST), Color(0, 0, 0), 3, 19, 14));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(SilverCOST), Color(0, 0, 0), 3, 19, 12.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(IronCOST), Color(0, 0, 0), 3, 19, 11));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(SteelCOST), Color(0, 0, 0), 3, 19, 9.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(CobaltCOST), Color(0, 0, 0), 3, 19, 8));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(CopperCOST), Color(0, 0, 0), 3, 19, 6.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(Coalcnt), Color(0, 0, 0), 3, 19, 5));
	}

	if (WorkStation::open && WorkStation::Fopen)
	{
		glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		_UIManager.renderMeshOnScreen(meshList[GEO_FURNACEUI], 40, 30, 50, 50);

		//buy
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(Scrapcnt) + " +", Color(0, 0, 0), 3, 15, 15));
	
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Gold")->second), Color(0, 0, 0), 3, 19, 12));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Silver")->second), Color(0, 0, 0), 3, 19, 10.8));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Iron")->second), Color(0, 0, 0), 3, 19, 9.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Steel")->second), Color(0, 0, 0), 3, 19, 8));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Cobalt")->second), Color(0, 0, 0), 3, 19, 6.8));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Copper")->second), Color(0, 0, 0), 3, 19, 5.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(_player.getInstance()->inventory_.container.find("Coal")->second), Color(0, 0, 0), 3, 19, 4.5));
	}

	if (WorkStation::open && WorkStation::Uopen)
	{
		glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		_UIManager.renderMeshOnScreen(meshList[GEO_UPGRADEUI], 40, 30, 50, 50);

		//count
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(WDcount) + " +", Color(0, 0, 0), 3, 15, 15));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(WAcount) + " +", Color(0, 0, 0), 3, 15, 13.5));
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(HPCount) + " +", Color(0, 0, 0), 3, 15, 11.8)); // 12
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(OxyCount) + " +", Color(0, 0, 0), 3, 15, 10.2)); // 11 
		_UIManager.renderTextOnScreen(UIManager::UI_Text("- " + to_string(StaCount) + " +", Color(0, 0, 0), 3, 15, 8.8)); // 10

		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(IronCost), Color(0, 0, 0), 3, 14, 7.2));
		_UIManager.renderTextOnScreen(UIManager::UI_Text(to_string(CobaltCost), Color(0, 0, 0), 3, 14, 6.2));		
	}
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Mouse: " + std::to_string(Application::MouseXPos_) + " , " + std::to_string(Application::MouseYPos_), Color(1, 1, 0), 2, 0.5, 26));
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
	_gameObjectMananger.removeAll();
}
