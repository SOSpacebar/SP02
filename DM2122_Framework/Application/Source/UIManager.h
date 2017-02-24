#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>
#include "Mesh.h"
#include "Vertex.h"

using std::string;

class Scene;

class UIManager
{
public:
	struct UI_Text
	{
		string message_;
		Color color_;
		float size_;
		float positionX_;
		float positionY_;

		
		UI_Text(string msg, Color c, float t_size, float posX, float posY) : message_(msg), color_(c), size_(t_size), positionX_(posX), positionY_(posY)  {}
	};

	UIManager();
	UIManager(Scene* scene);
	~UIManager();
	

	void renderTextOnScreen(UI_Text t);

	void renderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);

	void renderPlayerDetails();
private:
	Scene* scene_;
	Mesh* mesh_;
};




#endif