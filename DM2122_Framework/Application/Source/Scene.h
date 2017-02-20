#ifndef SCENE_H
#define SCENE_H

#include "Camera4.h"
#include "MatrixStack.h"

class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	Camera4 camera;
	MS modelStack, viewStack, projectionStack;
};

#endif