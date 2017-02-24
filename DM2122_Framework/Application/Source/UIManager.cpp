#include "UIManager.h"
#include "Scene.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

UIManager::UIManager()
{

}

UIManager::UIManager(Scene* scene) : scene_(scene) 
{
	mesh_ = scene_->meshList[Scene::GEO_TEXT];

}


UIManager::~UIManager()
{

}

void UIManager::renderPlayerDetails()
{
	//renderTextOnScreen(UIManager::UI_Text("Health : " + std::to_string(scene_->_player.getCurrentHealth()), Color(1, 1, 0), 2, 0.5, 28));
}

void UIManager::renderTextOnScreen(UI_Text t)
{
	if (!mesh_ || mesh_->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	scene_->projectionStack.PushMatrix();
	scene_->projectionStack.LoadMatrix(ortho);
	scene_->viewStack.PushMatrix();
	scene_->viewStack.LoadIdentity(); //No need camera for ortho mode
	scene_->modelStack.PushMatrix();
	scene_->modelStack.LoadIdentity(); //Reset modelStack
	scene_->modelStack.Scale(t.size_, t.size_, t.size_);
	scene_->modelStack.Translate(t.positionX_, t.positionY_, 0);

	glUniform1i(scene_->m_parameters[scene_->U_TEXT_ENABLED], 1);
	glUniform3fv(scene_->m_parameters[scene_->U_TEXT_COLOR], 1, &t.color_.r);
	glUniform1i(scene_->m_parameters[scene_->U_LIGHTENABLED], 0);
	glUniform1i(scene_->m_parameters[scene_->U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh_->textureID);
	glUniform1i(scene_->m_parameters[scene_->U_COLOR_TEXTURE], 0);


	for (unsigned i = 0; i < t.message_.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = scene_->projectionStack.Top() * scene_->viewStack.Top() * scene_->modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(scene_->m_parameters[scene_->U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh_->Render((unsigned)t.message_[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(scene_->m_parameters[scene_->U_TEXT_ENABLED], 0);

	scene_->projectionStack.PopMatrix();
	scene_->viewStack.PopMatrix();
	scene_->modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void UIManager::renderMeshOnScreen(Mesh* mesh,int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	scene_->projectionStack.PushMatrix();
	scene_->projectionStack.LoadMatrix(ortho);
	scene_->viewStack.PushMatrix();
	scene_->viewStack.LoadIdentity(); //No need camera for ortho mode
	scene_->modelStack.PushMatrix();
	scene_->modelStack.LoadIdentity();
	scene_->modelStack.Translate(x, y, 0);
	scene_->modelStack.Scale(sizex, sizey, 1);
	scene_->modelStack.Rotate(180, 0, 1, 0);
	scene_->RenderMesh(mesh, false); //UI should not have light
	scene_->projectionStack.PopMatrix();
	scene_->viewStack.PopMatrix();
	scene_->modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
