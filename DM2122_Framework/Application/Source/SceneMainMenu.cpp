#include "SceneMainMenu.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
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

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	dailycycle = 0;

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//enable mouse
	glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPos(Application::m_window, 400, 300);


	//Enable Camera
	camera.Init(Vector3(20, 5, -5), Vector3(0, 5, -5), Vector3(0, 1, 0));

	// Init VBO here
	FPS = 0;
	lightsOn = true;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1);
	//meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1, 1);
	//meshList[GEO_QUAD]->textureID = LoadTGA("Image//snowGround.tga");
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.545098f, 0, 0), 0.5f, 0.5f, 0.5f);
	//meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("blade", Color(1, 0, 1), 16, 1, 1);
	//meshList[GEO_ROOM] = MeshBuilder::GenerateQuad("Base", Color(1, 1, 1), 1, 1);
	//meshList[GEO_ROOM]->textureID = LoadTGA("Image//room.tga");
	//meshList[GEO_ROOMDOOR] = MeshBuilder::GenerateQuad("Basedoor", Color(1, 1, 1), 1, 1);
	//meshList[GEO_ROOMDOOR]->textureID = LoadTGA("Image//roomdoor.tga");
	meshList[GEO_SPACE] = MeshBuilder::GenerateQuad("space", Color(1, 1, 1), 1, 1);
	meshList[GEO_SPACE]->textureID = LoadTGA("Image//Space.tga");
	meshList[GEO_SUN] = MeshBuilder::GenerateQuad("sun", Color(1, 1, 1), 1, 1);
	meshList[GEO_SUN]->textureID = LoadTGA("Image//SpaceSun.tga");
	meshList[GEO_MOON] = MeshBuilder::GenerateQuad("moon", Color(1, 1, 1), 1, 1);
	meshList[GEO_MOON]->textureID = LoadTGA("Image//SpaceMoon.tga");
	//meshList[GEO_BLASTER] = MeshBuilder::GenerateOBJ("blaster", "OBJ//blaster.obj");
	//meshList[GEO_BLASTER]->textureID = LoadTGA("Image//blasterblue.tga");
	//meshList[GEO_LASERPROJ] = MeshBuilder::GenerateOBJ("laserProj", "OBJ//laserProjectile.obj");
	//meshList[GEO_LASERPROJ]->textureID = LoadTGA("Image//laserProjectileRed.tga");

	//meshList[GEO_CHEST] = MeshBuilder::GenerateOBJ("chest", "OBJ//Chest.obj");
	//meshList[GEO_CHEST]->textureID = LoadTGA("Image//Chest.tga");
	//meshList[GEO_ALIENPROBE] = MeshBuilder::GenerateOBJ("alienprobe", "OBJ//AlienProbe.obj");
	//meshList[GEO_ALIENPROBE]->textureID = LoadTGA("Image//AlienProbe.tga");
	//meshList[GEO_BEHOLDER] = MeshBuilder::GenerateOBJ("cylindertank", "OBJ//Beholder.obj");
	//meshList[GEO_BEHOLDER]->textureID = LoadTGA("Image//Beholder.tga");
	//meshList[GEO_STIMPAK] = MeshBuilder::GenerateOBJ("stimpak", "OBJ//Stimpak.obj");
	//meshList[GEO_STIMPAK]->textureID = LoadTGA("Image//Stimpak.tga");


	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//CandaraFont.tga");


	//meshList[GEO_COAL] = MeshBuilder::GenerateOBJ("Coal", "OBJ//coal.obj");
	//meshList[GEO_COAL]->textureID = LoadTGA("Image//coal.tga");

	//meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//iron.obj");
	//meshList[GEO_IRON]->textureID = LoadTGA("Image//iron.tga");

	//meshList[GEO_COBALT] = MeshBuilder::GenerateOBJ("cobalt", "OBJ//cobalt.obj");
	//meshList[GEO_COBALT]->textureID = LoadTGA("Image//cobalt.tga");

	//For UI assign(Make sure its after meshList)
	UIManager _UI(this);
	Scene::_UIManager = _UI;


	Mtx44 projection;
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 2000.0f);
	projectionStack.LoadMatrix(projection);



	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

}

void MainMenu::Update(double dt)
{
	FPS = (float)(1.0f / dt);

	dt_ = dt;

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

	if (Application::mouseClicked == true && Application::MouseXPos_ >= 300 && Application::MouseXPos_<=500 && Application::MouseYPos_ >= 175 && Application::MouseYPos_ <= 230)
		SceneManager::instance()->SetNextScene(1);
	if (Application::mouseClicked == true && Application::MouseXPos_ >= 300 && Application::MouseXPos_ <= 500 && Application::MouseYPos_ >= 375 && Application::MouseYPos_ <= 430)
	{
		Application::Exit();
	}
	//if (camera.position.x > 25 && camera.position.z > -10 && camera.position.z<0)
	//	SceneManager::instance()->SetNextScene(0);

	dailycycle += 0.5 * dt;

	camera.Update(dt);
	camera.getCollider().updateColliderPos(camera.position);
	_gameObjectMananger.update(camera);
}

void MainMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	RenderSkybox();

	//FPS
	_UIManager.renderTextOnScreen(UIManager::UI_Text("FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19));
	//player position
	_UIManager.renderTextOnScreen(UIManager::UI_Text("Mouse: " + std::to_string(Application::MouseXPos_ )+ " , " + std::to_string(Application::MouseYPos_), Color(1, 1, 0), 2, 0.5, 26));

	_UIManager.renderTextOnScreen(UIManager::UI_Text("PLAY", Color(1, 1, 0), 10, 3.5, 4));

	_UIManager.renderTextOnScreen(UIManager::UI_Text("EXIT", Color(1, 1, 0), 10, 3.5, 2));


}

//void MainMenu::RenderMesh(Mesh *mesh, bool enableLight)
//{
//}

void MainMenu::RenderSkybox()
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

//void MainMenu::RenderText(Mesh* mesh, std::string text, Color color)
//{
//}

void MainMenu::Exit()
{
	glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}