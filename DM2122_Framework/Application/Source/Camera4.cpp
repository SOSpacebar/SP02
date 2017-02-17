#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

Camera4::Camera4()
{
}

Camera4::~Camera4()
{
}

void Camera4::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	turnDir = 0;
}

void Camera4::Update(double dt)
{
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	static const float CAMERA_SPEED = 5.f;

	Mtx44 rotateX, rotateY;
	rotateX.SetToRotation(Application::yaw_, 0, -1, 0);
	rotateY.SetToRotation(Application::pitch_, right.x, 0, right.z);
	//set view target up
	view = rotateX* rotateY* view;
	target = position + view;
	up = rotateX* rotateY * up;

	Application::pitch_ = 0;
	Application::yaw_ = 0;


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
		position = position + view;
		//normal
		//position.x = position.x + view.x;
		//position.z = position.z + view.z;

		//camera
		target = position + view;
	}
	 if (Application::IsKeyPressed('S'))
	{
		//no clip
		position = position - view;

		//normal
		//position.x = position.x - view.x;
		//position.z = position.z - view.z;

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

		Vector3 view = (target - position).Normalized();
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
		Vector3 view = (target - position).Normalized();
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
	}

	BoundsCheck(view);
}

void Camera4::Reset()
{
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
	if (position.z < -200)
	{
		position.z = -200;
		target = position + view;
	}
	if (position.z > 200)
	{
		position.z = 200;
		target = position + view;
	}
}
