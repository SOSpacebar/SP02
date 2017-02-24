
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneManager.h"

GLFWwindow*Application::m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
float Application::MouseXPos_;
float Application::MouseYPos_;
bool Application::mouseClicked = false;
bool Application::cantSpam = false;
//float lastX = 400, lastY = 300;

static int nextSceneNo;
static bool changeScene;

SceneManager *SceneManager::s_instance = 0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursorPositionCallback(GLFWwindow*window, double xPos, double yPos)
{
	Application::MouseXPos_ = xPos;
	Application::MouseYPos_ = yPos;
}

static void mouseButtonCallback(GLFWwindow*window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Application::mouseClicked = true;
		std::cout << "Fire" << std::endl;
	}
	else if (action == GLFW_RELEASE)
	{
		Application::mouseClicked = false;;
	}
}


bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
	nextSceneNo = 0;
	changeScene = false;
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(800, 600, "Computer Graphics", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);
	//mouse stuff
	glfwSetCursorPosCallback(m_window, cursorPositionCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

//void Application::ChangeScene(int sceneNo)
//{
//	nextSceneNo = sceneNo;
//	changeScene = true;
//}

void Application::Run()
{

	//SceneManager::instance()->AddScene(new SP02);
	//SceneManager::instance()->AddScene(new SceneBase);
	SceneManager::instance()->AddScene(new TScene);

	SceneManager::instance()->AddScene(new MainMenu);
	SceneManager::instance()->AddScene(new SP02);
	SceneManager::instance()->AddScene(new SceneBase);

	SceneManager::instance()->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		SceneManager::instance()->Update();
		SceneManager::instance()->Update(m_timer.getElapsedTime());
		SceneManager::instance()->Render();

		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	
	SceneManager::instance()->Exit();
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
