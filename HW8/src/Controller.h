#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// �����״̬
enum State {
	ACTIVE,
	END
};

class Controller
{
public:
	// �����״̬
	State              State;
	// ���ڵĿ��
	GLuint             Width, Height;

	Controller(GLuint width, GLuint height);
	~Controller();
	// ��ʼ������shader��
	void Init();
	// ��������
	void ProcessInput(GLfloat dt);
	// ���¶���
	void Update(GLfloat dt);
	// ��ʼ��Ⱦ
	void Render(float rotateRad);
	// ��������ƶ�
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	// ��ӵ�
	void AddUserPoint(float posX, float posY);
	// ɾ����
	void DeleteUserPoint();
	// ����Bernstein������
	float countBernstein(int i, int n, float t);
	// �׳�
	float Factorial(int x);
};

#endif