#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 程序的状态
enum State {
	ACTIVE,
	END
};

class Controller
{
public:
	// 程序的状态
	State              State;
	// 窗口的宽高
	GLuint             Width, Height;

	Controller(GLuint width, GLuint height);
	~Controller();
	// 初始化加载shader等
	void Init();
	// 处理输入
	void ProcessInput(GLfloat dt);
	// 更新顶点
	void Update(GLfloat dt);
	// 开始渲染
	void Render(float rotateRad);
	// 处理鼠标移动
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	// 添加点
	void AddUserPoint(float posX, float posY);
	// 删除点
	void DeleteUserPoint();
	// 计算Bernstein基函数
	float countBernstein(int i, int n, float t);
	// 阶乘
	float Factorial(int x);
};

#endif