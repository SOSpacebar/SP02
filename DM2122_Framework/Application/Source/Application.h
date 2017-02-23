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
	static float MouseXPos_;
	static float MouseYPos_;
	static bool mouseClicked;
	static bool cantSpam;

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif