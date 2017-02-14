#include "SceneManager.h"

SceneManager::SceneManager() : currSceneID(0), nextSceneID(0), sceneID(0)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::AddScene(Scene *scene)
{
	sceneData[sceneID] = scene;
	sceneID++;
}

void SceneManager::SetNextScene(int sceneID)
{
	nextSceneID = sceneID;
}

void SceneManager::Init()
{
	sceneData[currSceneID]->Init();
}


void SceneManager::Update()
{
	Scene *scene = sceneData[currSceneID];

	if (currSceneID != nextSceneID)
	{
		currSceneID = nextSceneID;
		scene->Exit();
		scene = sceneData[nextSceneID];
		scene->Init();
	}
}

void SceneManager::Update(double dt)
{
	sceneData[currSceneID]-> Update(dt);
}

void SceneManager::Render()
{
	sceneData[currSceneID]->Render();
}

void SceneManager::Exit()
{
	sceneData[currSceneID]->Exit();
}