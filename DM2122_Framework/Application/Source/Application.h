#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	//static void ChangeScene(int sceneNo);
	static float pitch_;
	static float yaw_;

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif