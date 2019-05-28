#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Camera
{
public:
	// 键盘移动
	void moveForward(float deltaTime);
	void moveBack(float deltaTime);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	// 鼠标移动
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	// 鼠标滚动
	void ProcessMouseScroll(float yoffset);
	// 获取view矩阵
	glm::mat4 GetViewMatrix();

	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// 获取视角值
	float getZoom();

	glm::vec3 Position;
private:

	// 摄像机的属性
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// 欧拉角
	float Yaw;       // 偏航角
	float Pitch;     // 俯仰角

	float MovementSpeed;      // 相机移动速度
	float MouseSensitivity;   // 鼠标灵敏度
	float Zoom;               // 缩放视野

	void updateCameraVectors();

};

