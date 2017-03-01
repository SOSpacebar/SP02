#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <map>

#include "SceneUI.h"
#include "Assignment03.h"
#include "SP02.h"
#include "SceneBase.h"
#include "SceneMainMenu.h"
#include "TScene.h"
#include "SceneLoading.h"
#include "SceneEnd.h"

using std::map;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void AddScene(Scene *scene);
	void SetNextScene(int sceneID);
	void Init();
	void Update();
	void Update(double dt);
	void Render();
	void Exit();

	static SceneManager *instance()
	{
		if (!s_instance)
			s_instance = new SceneManager;
		return s_instance;
	}
private:
	int currSceneID, nextSceneID, sceneID;
	static SceneManager *s_instance;
	map<int, Scene*> sceneData;
};

#endif