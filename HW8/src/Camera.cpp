#include "Camera.h"

const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

void Camera::updateCameraVectors()
{
	// 计算照相机向前的向量
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// 计算照相机向右的向量
	Right = glm::normalize(glm::cross(Front, WorldUp));
	// 计算照相机向上的向量
	Up = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

void Camera::moveForward(float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	Position += Front * velocity;
}
void Camera::moveBack(float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	Position -= Front * velocity;
}
void Camera::moveRight(float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	Position += Right * velocity;
}
void Camera::moveLeft(float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	Position -= Right * velocity;
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// 是否锁定俯仰角的范围
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
	// 视野的变换
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}
float Camera::getZoom()
{
	return Zoom;
}