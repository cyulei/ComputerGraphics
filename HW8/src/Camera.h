#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Camera
{
public:
	// �����ƶ�
	void moveForward(float deltaTime);
	void moveBack(float deltaTime);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	// ����ƶ�
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	// ������
	void ProcessMouseScroll(float yoffset);
	// ��ȡview����
	glm::mat4 GetViewMatrix();

	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// ��ȡ�ӽ�ֵ
	float getZoom();

	glm::vec3 Position;
private:

	// �����������
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// ŷ����
	float Yaw;       // ƫ����
	float Pitch;     // ������

	float MovementSpeed;      // ����ƶ��ٶ�
	float MouseSensitivity;   // ���������
	float Zoom;               // ������Ұ

	void updateCameraVectors();

};

