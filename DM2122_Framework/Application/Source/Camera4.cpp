#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

Camera4::Camera4() : _collider(&position, Vector3(2, 1, 2))
{
}

Camera4::~Camera4()
{
}

void Camera4::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	GodMode = false;
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	turnDir = 0;
	pitch_ = 0;
	yaw_ = 0;
	lastX = 0, lastY = 0;

}

void Camera4::Update(double dt)
{
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	static const float CAMERA_SPEED = 100.f;
	Mtx44 rotateX, rotateY;
	bool firstMouse = true;
	float sensitivity = 0.1;

	float xoffset = Application::MouseXPos_ - lastX;
	float yoffset = lastY - Application::MouseYPos_;

	lastX = Application::MouseXPos_;
	lastY = Application::MouseYPos_;

	if (firstMouse)
	{
		lastX = Application::MouseXPos_;
		lastY = Application::MouseYPos_;
		firstMouse = false;
	}

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw_ += xoffset;
	pitch_ += yoffset;

	rotateX.SetToRotation(yaw_, 0, -1, 0);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	rotateY.SetToRotation(pitch_, right.x, 0, right.z);

	view = rotateX* rotateY* view;
	target = position + view;
	up = rotateX* rotateY * up;
	pitch_ = 0;
	yaw_ = 0;
	
	
	if(Application::IsKeyPressed(VK_SPACE))
	std::cout << view << " : " << right << " : " << up << std::endl;

	//Camera Controls
	if (Application::IsKeyPressed('A'))
	{
		position = position - right;
		target = position + view;

	}
	 if (Application::IsKeyPressed('D'))
	{
		position = position + right;
		target = position + view;
	}
	 if (Application::IsKeyPressed('W'))
	{
		//no clip
		if (GodMode == true)
			position = position + view;
		//normal
		else
		{
			position.x = position.x + view.x;
			position.z = position.z + view.z;
		}

		//camera
		target = position + view;
	}
	 if (Application::IsKeyPressed('S'))
	{
		//no clip
		if (GodMode == true)
		position = position - view;
		else
		{
			//normal
			position.x = position.x - view.x;
			position.z = position.z - view.z;
		}
		//camera
		target = position + view;
	}
	else if (Application::IsKeyPressed(VK_LEFT))
	{
		float yaw = (float)(CAMERA_SPEED * dt);
		turnDir += (float)(CAMERA_SPEED * dt);

		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	else if (Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = (float)(-CAMERA_SPEED * dt);
		turnDir -= (float)(CAMERA_SPEED * dt);

		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	else if (Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(CAMERA_SPEED * dt);

		view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);

		view = rotation * view;
		target = position + view;
	}
	else if (Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);

		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed('R'))
	{
		Reset();
		if (GodMode == true)
			std::cout << "true" << std::endl;
		else
			std::cout << "false" << std::endl;
	}

	BoundsCheck(view);
}

void Camera4::Reset()
{
	if (GodMode == true)
		GodMode = false;
	else if (GodMode == false)
		GodMode = true;

	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

void Camera4::BoundsCheck(const Vector3& view)
{
	//Simple Bounds Check
	if (position.x < -150)
	{
		position.x = -150;
		target = position + view;
	}
	if (position.x > 150)
	{
		position.x = 150;
		target = position + view;
	}
	if (position.z < -150)
	{
		position.z = -150;
		target = position + view;
	}
	if (position.z > 150)
	{
		position.z = 150;
		target = position + view;
	}
}
