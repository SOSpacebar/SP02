#include "SceneUI.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"

#include "MyMath.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"

SceneUI::SceneUI()
{
}

SceneUI::~SceneUI()
{
}

void SceneUI::Init()
{
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable Camera
	camera.Init(Vector3(5, 5, 5), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Init VBO here
	FPS = 0;
	rotatAngle = 0;
	rotatAngleMartix = 0;
	translateX = 0;
	translateY = 30;
	scaleAll = 1;
	lightsOn = true;
	saberOn = false;

	openDoor = false;
	lightSaberPickedUp = false;

	saberPosition = 0;
	handPosition = camera.position;

	translateDoorX = 0;
	gravity = 10;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	for (size_t i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = 0;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1, 1);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Mushroom.tga");
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.545098f, 0, 0), 0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("blade", Color(1, 0, 1), 16, 1, 1);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1, 1);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1, 1);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1, 1);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1, 1);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1, 1);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1, 1);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_BODY] = MeshBuilder::GenerateSphere("body", Color(0.902f, 0.902f, 0.980f), 18, 36, 2);
	meshList[GEO_HEAD] = MeshBuilder::GenerateHemisphere("head", Color(0.902f, 0.902f, 0.980f), 18, 36, 2);
	meshList[GEO_EYE] = MeshBuilder::GenerateHemisphere("eye", Color(0, 0, 0), 18, 36, 2);
	meshList[GEO_EYE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYE]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE]->material.kShininess = 1.f;
	meshList[GEO_BB8DETAILS] = MeshBuilder::GenerateHemisphere("details", Color(1, 0.647f, 0), 18, 36, 2);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.255f, 0.412f, 0.882f), 18, 3, 3);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//CandaraFont.tga");

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
	light[1].position.Set(saberPosition.x, saberPosition.y, saberPosition.z);
	light[1].color.Set(1, 0, 1);
	light[1].power = 0;
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
}

void SceneUI::Update(double dt)
{
	Math::InitRNG();
	rotatAngle += (float)(10 * dt);
	FPS = (float)(1.0f / dt);

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


	if (Application::IsKeyPressed(VK_F1))
		//Application::ChangeScene(1);
//
//
//	if (Application::IsKeyPressed('E'))
//	{
//		float distanceToSaber = ((camera.position + saberPosition).Dot(saberPosition + camera.position));
//
//		if (camera.position.x < -55 && camera.position.x > -65 && camera.position.z < -125 && camera.position.z > -140)
//			openDoor = true;
//
//		if (distanceToSaber < 150 && lightSaberPickedUp == false)
//			lightSaberPickedUp = true;
//	}
//
//	if (Application::IsKeyPressed('F') && lightSaberPickedUp == true)
//	{
//		light[1].power = 1;
//		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
//		saberOn = true;
//	}
//
//	if (Application::IsKeyPressed('G') && lightSaberPickedUp == true)
//	{
//		light[1].power = 0;
//		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
//		saberOn = false;
//	}
//
//	if (openDoor)
//	{
//		if (translateDoorX < 5)
//			translateDoorX += 5 * dt;
//	}
//
//	if (lightSaberPickedUp == true)
//		light[1].position.Set(camera.position.x - 7, camera.position.y - 3, camera.position.z - 3);
//
	camera.Update(dt);
}
//
void SceneUI::Render()
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

	RenderMeshOnScreen(meshList[GEO_QUAD], 5, 5, 5, 5);
//
//	//Ground
//	modelStack.PushMatrix();
//	modelStack.Scale(300, 1, 200);
//	modelStack.Rotate(90, 1, 0, 0);
//	RenderMesh(meshList[GEO_QUAD], true);
//	modelStack.PopMatrix();
//
//	//2nd Ground
//	modelStack.PushMatrix();
//	modelStack.Translate(0, 0, -175);
//	modelStack.Scale(300, 1, 200);
//	modelStack.Rotate(90, 1, 0, 0);
//	RenderMesh(meshList[GEO_QUAD], true);
//	modelStack.PopMatrix();
//
//	renderBB8();
//
//	modelStack.PushMatrix();
//	modelStack.Translate(35, 0, -40);
//	modelStack.Scale(0.05f, 0.05f, 0.05f);
//	RenderMesh(meshList[GEO_MODEL1], true);
//	modelStack.PopMatrix();
//
//
//	if (lightSaberPickedUp == false)
//	{
//		modelStack.PushMatrix();
//		modelStack.Translate(saberPosition.x, saberPosition.y, saberPosition.z);
//		modelStack.Scale(0.05f, 0.05f, 0.05f);
//		RenderMesh(meshList[GEO_MODEL2], true);
//		modelStack.PopMatrix();
//	}
//
//	//modelStack.PushMatrix();
//	//modelStack.Translate(0, 5, 0);
//	//modelStack.Scale(0.05f, 0.05f, 0.05f);
//	//RenderMesh(meshList[GEO_MODEL3], true);
//	//modelStack.PopMatrix();
//
//	modelStack.PushMatrix();
//	modelStack.Translate(10, -0.5f, 0);
//	//modelStack.Scale(5, 5, 5);
//	RenderMesh(meshList[GEO_ROCK1], true);
//	modelStack.PopMatrix();
//
//	modelStack.PushMatrix();
//	modelStack.Translate(15, -0.5f, 20);
//	//modelStack.Scale(5, 5, 5);
//	RenderMesh(meshList[GEO_ROCK2], true);
//	modelStack.PopMatrix();
//
//	modelStack.PushMatrix();
//	modelStack.Translate(-65, -0.5f, -120);
//	modelStack.Scale(0.1f, 0.1f, 0.1f);
//	RenderMesh(meshList[GEO_BASE], true);
//	modelStack.PopMatrix();
//
//	modelStack.PushMatrix();
//	modelStack.Translate(-60 + (float)translateDoorX, -0.5f, -125);
//	modelStack.Scale(0.1f, 0.1f, 0.1f);
//	RenderMesh(meshList[GEO_DOOR_L], true);
//	modelStack.PopMatrix();
//
//	modelStack.PushMatrix();
//	modelStack.Translate(-70 - (float)translateDoorX, -0.5f, -113.5f);
//	modelStack.Scale(0.1f, 0.1f, 0.1f);
//	RenderMesh(meshList[GEO_DOOR_R], true);
//	modelStack.PopMatrix();
//
//
//	renderArea1Rocks();
//
//
//
//	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: " + std::to_string(FPS), Color(0, 1, 0), 3, .5f, 19);
//
//	if (camera.position.x < -55 && camera.position.x > -65 && camera.position.z < -125 && camera.position.z > -140 && !openDoor)
//		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' To Open Door", Color(0, 1, 0), 2, .5f, 15.f);
//
//	if ((camera.position + saberPosition).Dot(saberPosition + camera.position) < 150 && lightSaberPickedUp == false)
//		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' To Equip LightSaber", Color(0, 1, 0), 2, .5f, 15.f);
//
//	if (lightSaberPickedUp == true)
//	{
//		RenderTextOnScreen(meshList[GEO_TEXT], "LightSaber Equipped", Color(0, 1, 0), 3, .5f, 1.5f);
//		if (saberOn == true)
//			RenderTextOnScreen(meshList[GEO_TEXT], "States: On", Color(0, 1, 0), 3, .5f, .5f);
//		else
//			RenderTextOnScreen(meshList[GEO_TEXT], "States: Off", Color(0, 1, 0), 3, .5f, .5f);
//	}
//
//	
//
//	DebugCamPosition();

	
}

void SceneUI::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && lightsOn)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}


	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}

	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void SceneUI::RenderSkybox()
{
	float offset = 5.f;

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 500 - offset + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, -500 + offset + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(500 - offset + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-500 + offset + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, -500 + offset + camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, 500 - offset + camera.position.z);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
}

void SceneUI::renderBB8()
{
	modelStack.PushMatrix(); //Body
	modelStack.Translate(camera.position.x, 1.5f, camera.position.z);
	modelStack.Rotate(camera.turnDir - 135.f, 0, 1, 0);

	if (lightSaberPickedUp == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(handPosition.x - 7, handPosition.y - 3.f, handPosition.z - 3);
		modelStack.Rotate(-135, 0, 0, 1);
		modelStack.Scale(0.05f, 0.05f, 0.05f);

		RenderMesh(meshList[GEO_MODEL2], true);

		modelStack.PopMatrix();

		if (saberOn == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(handPosition.x - 7, handPosition.y - 3.30f, handPosition.z - 3);
			modelStack.Rotate(135, 0, 0, 1);
			modelStack.Scale(0.1f, 8, 0.1f);

			RenderMesh(meshList[GEO_CYLINDER], true);

			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix(); //Head
	modelStack.Translate(0, 1.8f, 0);

	modelStack.PushMatrix(); //Main Eye
	modelStack.Rotate(75, 1, 0, 0);
	modelStack.Translate(0, 1, -0.8f);
	modelStack.Scale(0.2f, 0.2f, 0.2f);
	RenderMesh(meshList[GEO_EYE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Side Eye
	modelStack.Rotate(75, 1, 0, 0);
	modelStack.Translate(0.5f, 1, -0.25f);
	modelStack.Scale(0.15f, 0.15f, 0.15f);
	RenderMesh(meshList[GEO_EYE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Antenna
	modelStack.Rotate(45, 0, 1, 0);
	modelStack.Translate(0.5f, 1.25f, -0.25f);
	modelStack.Scale(0.1f, 2.5f, 0.1f);
	RenderMesh(meshList[GEO_CUBE], true);
	modelStack.PopMatrix();

	modelStack.Scale(0.7f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Top Detail
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(0.75f, 0.5f, 0.75f);
	RenderMesh(meshList[GEO_BB8DETAILS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Front Detail
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(0.75f, 0.5f, 0.75f);
	RenderMesh(meshList[GEO_BB8DETAILS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Back Detail
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(0.75f, 0.5f, 0.75f);
	RenderMesh(meshList[GEO_BB8DETAILS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Bottom Detail
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(0.75f, 0.5f, 0.75f);
	RenderMesh(meshList[GEO_BB8DETAILS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Right Detail
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(0.75f, 0.5f, 0.75f);
	RenderMesh(meshList[GEO_BB8DETAILS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Left Detail
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(0.75f, 0.5f, 0.75f);
	RenderMesh(meshList[GEO_BB8DETAILS], true);
	modelStack.PopMatrix();

	RenderMesh(meshList[GEO_BODY], true);
	modelStack.PopMatrix();
}

void SceneUI::renderArea1Rocks()
{
	//Render Walls 
	//Left
	modelStack.PushMatrix();
	modelStack.Translate(-80, -0.5f, 40);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-80, -0.5f, -40);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-85, -0.5f, 20);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-85, -0.5f, 80);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-85, -0.5f, -40);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	//Right
	modelStack.PushMatrix();
	modelStack.Translate(80, -0.5f, 40);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(80, -0.5f, -40);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(85, -0.5f, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(85, -0.5f, 40);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(85, -0.5f, -60);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	//Front
	modelStack.PushMatrix();
	modelStack.Translate(40, -0.5f, 80);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, -0.5f, 80);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20, -0.5f, 85);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(80, -0.5f, 85);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, -0.5f, 85);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	//Back
	modelStack.PushMatrix();
	modelStack.Translate(40, -0.5f, -80);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(5, 5, 30);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60, -0.5f, -80);
	//modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROCK3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20, -0.5f, -85);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(80, -0.5f, -85);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, -0.5f, -85);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	//Render the 4 Pillars
	modelStack.PushMatrix();
	modelStack.Translate(100, -0.5f, 100);
	modelStack.Scale(5, 10, 5);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, -0.5f, 100);
	modelStack.Scale(5, 10, 5);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, -0.5f, -100);
	modelStack.Scale(5, 10, 5);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, -0.5f, -100);
	modelStack.Scale(5, 10, 5);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();
}

void SceneUI::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneUI::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneUI::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Scale((float)sizex, (float)sizey, 1);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneUI::DebugCamPosition()
{


	//RenderTextOnScreen(meshList[GEO_TEXT], "x:" + std::to_string(camera.position.x), Color(0, 1, 0), 3, .5f, .5f);
	//RenderTextOnScreen(meshList[GEO_TEXT], "y:" + std::to_string(camera.position.y), Color(0, 1, 0), 3, .5f, 1.0f);
	//RenderTextOnScreen(meshList[GEO_TEXT], "z:" + std::to_string(camera.position.z), Color(0, 1, 0), 3, .5f, 1.5f);

	//RenderTextOnScreen(meshList[GEO_TEXT], "turnDir:" + std::to_string(camera.turnDir), Color(0, 1, 0), 3, .5f, 2.f);
}

void SceneUI::Exit()
{
	// Cleanup VBO here
	for (size_t i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i] != NULL)
			delete meshList[i];
	}

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}