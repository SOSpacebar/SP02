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

GameObjectManager SP02::_gameObjectMananger;

SP02::SP02()
{
}

SP02::~SP02()
{
}

void SP02::Init()
{
	dailycycle = 0;
	//random seed
	srand(time(NULL));
	//random amounts of coal
	for (int i = 0; i < 150 ; i++)
	{
		randomx = rand() % 300;
		RandXArray[i] = randomx;
		randomz = rand() % 300;
		RandZArray[i] = randomz;
	}
	//random amounts of coal
	for (int i = 0; i < 100; i++)
	{
		irandomx = rand() % 300;
		IRandXArray[i] = irandomx;
		irandomz = rand() % 300;
		IRandZArray[i] = irandomz;
	}
	//random amounts of cobalt
	for (int i = 0; i < 50; i++)
	{
		crandomx = rand() % 300;
		CRandXArray[i] = crandomx;
		crandomz = rand() % 300;
		CRandZArray[i] = crandomz;
	}

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
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1, 1);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//snowGround.tga");
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
	meshList[GEO_BLASTER] = MeshBuilder::GenerateOBJ("blaster", "OBJ//blaster.obj");
	meshList[GEO_BLASTER]->textureID = LoadTGA("Image//blasterblue.tga");


	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//CandaraFont.tga");


	meshList[GEO_COAL] = MeshBuilder::GenerateOBJ("Coal", "OBJ//coal.obj");
	meshList[GEO_COAL]->textureID = LoadTGA("Image//coal.tga");

	meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//iron.obj");
	meshList[GEO_IRON]->textureID = LoadTGA("Image//iron.tga");

	meshList[GEO_COBALT] = MeshBuilder::GenerateOBJ("cobalt", "OBJ//cobalt.obj");
	meshList[GEO_COBALT]->textureID = LoadTGA("Image//cobalt.tga");


	Mtx44 projection;
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 2000.0f);
	projectionStack.LoadMatrix(projection);

	light[0].type = Light::LIGHT_SPOT;
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

	//_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Characters(this,"box" ,Vector3(0,0,0)));
	//_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Characters(this,"box1", Vector3(0, 0, 40)));
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Vein(this, "vein", Vector3(0, 0, 0)));
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Vein(this, "vein1", Vector3(0, 0, 40)));
	_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Vein(this, "vein2", Vector3(0, 0, -40)));
	//_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Characters("box2", Vector3(60, 0, 60)));
	//_gameObjectMananger.remove(box);
	_gameObjectMananger.add(GameObjectManager::objectType::T_INTERACTABLE, new Weapon(this, "blaster", Vector3(0, 5, 0), 0, 0));
}

void SP02::Update(double dt)
{
	Math::InitRNG();
	FPS = (float)(1.0f / dt);

	_dt = dt;    

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

	if (Application::mouseClicked)
	{
		_gameObjectMananger.add(GameObjectManager::objectType::T_ENVIRONMENTAL, new Bullet(this, "Bullet", camera.position, Vector3(4, 4, 4)));
	}
		
	if (Application::IsKeyPressed(VK_F1))
		SceneManager::instance()->SetNextScene(0);
	//if (camera.position.x > 25 && camera.position.z > -10 && camera.position.z<0)
	//	SceneManager::instance()->SetNextScene(0);

	dailycycle += 0.1 * dt;

	camera.Update(dt);
	camera.getCollider().updateColliderPos(camera.position);
	_gameObjectMananger.update(camera);


	if (Application::IsKeyPressed('Z'))
	{
		player.inventory_.push("Iron",1);//player picks up 1 element iron
	}
	if (Application::IsKeyPressed('X'))
	{
		player.inventory_.push("Copper", 1);
	}
	if (Application::IsKeyPressed('C'))
	{
		player.inventory_.push("Silver", 1);
	}
	if (Application::IsKeyPressed('V'))
	{
		player.inventory_.push("Gold", 1);
	}
	if (Application::IsKeyPressed('B'))
	{
		player.inventory_.push("Steel", 1);
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

	//randomly spawned objects
	/*for (int i = 0; i < 150; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(RandXArray[i] - 150, 0, RandZArray[i] - 150);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_COAL], false);
		modelStack.PopMatrix();
	}
	for (int i = 0; i < 100; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(IRandXArray[i] - 150, 0, IRandZArray[i]-150);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_IRON], false);
		modelStack.PopMatrix();
	}
	for (int i = 0; i < 50; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(CRandXArray[i]-150, 0, CRandZArray[i]-150);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_COBALT], false);
		modelStack.PopMatrix();
	}*/

	//rest of the base
	//top
	//modelStack.PushMatrix();
	//modelStack.Translate(55, 25, 0);
	//modelStack.Rotate(-90, 1, 0, 0);
	//modelStack.Rotate(90, 0, 0, 1);
	//modelStack.Scale(50, 50, 50);
	//RenderMesh(meshList[GEO_ROOM], false);
	//modelStack.PopMatrix();
	////bot
	//modelStack.PushMatrix();
	//modelStack.Translate(55, 0.1, 0);
	//modelStack.Rotate(90, 1, 0, 0);
	//modelStack.Rotate(-90, 0, 0, 1);
	//modelStack.Scale(50, 50, 50);
	//RenderMesh(meshList[GEO_ROOM], false);
	//modelStack.PopMatrix();
	////back
	//modelStack.PushMatrix();
	//modelStack.Translate(80, 12.5, 0);
	//modelStack.Rotate(-90, 0, 1, 0);
	//modelStack.Scale(50, 25, 50);
	//RenderMesh(meshList[GEO_ROOM], false);
	//modelStack.PopMatrix();
	////side
	//modelStack.PushMatrix();
	//modelStack.Translate(55, 12.5, -25);
	//modelStack.Rotate(180, 0, 1, 0);
	//modelStack.Scale(50, 25, 50);
	//RenderMesh(meshList[GEO_ROOM], false);
	//modelStack.PopMatrix();
	////other side
	//modelStack.PushMatrix();
	//modelStack.Translate(55, 12.5, 25);
	//modelStack.Scale(50, 25, 50);
	//RenderMesh(meshList[GEO_ROOM], false);
	//modelStack.PopMatrix();
	////basedoor
	//modelStack.PushMatrix();
	//modelStack.Translate(30, 12.5, 0);
	//modelStack.Rotate(-90, 0, 1, 0);
	//modelStack.Scale(50, 25, 50);
	//RenderMesh(meshList[GEO_ROOMDOOR], false);
	//modelStack.PopMatrix();

	
	//render item on hand
	//modelStack.PushMatrix();
	//modelStack.Translate(camera.target.x,camera.target.y -0.5,camera.target.z);
	//modelStack.Scale(0.5, 0.5, 0.5);
	//RenderMesh(meshList[GEO_CUBE], false);
	//modelStack.PopMatrix();

	_gameObjectMananger.renderGameObjects();

	//FPS
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19);
	//player position
	RenderTextOnScreen(meshList[GEO_TEXT], "Position: " + std::to_string(camera.position.x) + " , " + std::to_string(camera.position.z), Color(1, 1, 0), 2, 0, 26);
	//inventory
	RenderTextOnScreen(meshList[GEO_TEXT], "Iron : " + std::to_string(player.inventory_.container.find("Iron")->second) , Color(1, 1, 0), 2, 1, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], "Copper : " + std::to_string(player.inventory_.container.find("Copper")->second), Color(1, 1, 0), 2, 1, 16);
	RenderTextOnScreen(meshList[GEO_TEXT], "Silver : " + std::to_string(player.inventory_.container.find("Silver")->second), Color(1, 1, 0), 2, 1, 17);
	RenderTextOnScreen(meshList[GEO_TEXT], "Gold : " + std::to_string(player.inventory_.container.find("Gold")->second), Color(1, 1, 0), 2, 1, 18);
	RenderTextOnScreen(meshList[GEO_TEXT], "Steel : " + std::to_string(player.inventory_.container.find("Steel")->second), Color(1, 1, 0), 2, 1, 14);

	DebugCamPosition();
}

//void SP02::RenderMesh(Mesh *mesh, bool enableLight)
//{
//	Mtx44 MVP, modelView, modelView_inverse_transpose;
//
//	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//	modelView = viewStack.Top() * modelStack.Top();
//	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
//	if (enableLight && lightsOn)
//	{
//		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
//		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
//		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
//
//		//load material
//		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
//		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
//		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
//		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
//	}
//	else
//	{
//		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	}
//
//
//	if (mesh->textureID > 0)
//	{
//		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//	}
//
//	else
//	{
//		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
//	}
//
//	mesh->Render();
//
//	if (mesh->textureID > 0)
//	{
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//
//}

void SP02::RenderSkybox()
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

void SP02::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * .5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP02::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SP02::DebugCamPosition()
{
	/*RenderTextOnScreen(meshList[GEO_TEXT], "x:" + std::to_string(camera.position.x), Color(0, 1, 0), 3, .5f, .5f);
	RenderTextOnScreen(meshList[GEO_TEXT], "y:" + std::to_string(camera.position.y), Color(0, 1, 0), 3, .5f, 1.0f);
	RenderTextOnScreen(meshList[GEO_TEXT], "z:" + std::to_string(camera.position.z), Color(0, 1, 0), 3, .5f, 1.5f);*/
}

void SP02::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}