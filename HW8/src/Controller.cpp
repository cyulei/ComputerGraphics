#include "Controller.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include <vector>
#include <iostream>
#include <math.h>

float bigPointSize = 20;
// 渲染
SpriteRenderer  *Renderer;
// 摄像机
Camera *MainCamera;
// 用户的点
std::vector<glm::vec2> userPoint;
// 生成的曲线点
std::vector<glm::vec2> curvePoint;
Controller::Controller(GLuint width, GLuint height)
	: State(ACTIVE), Width(width), Height(height)
{

}

Controller::~Controller()
{
	delete Renderer;
}

void Controller::Init()
{
	// 加载shader
	ResourceManager::LoadShader("testV.vs", "testF.frag", nullptr, "sprite");

	Shader *temp = ResourceManager::GetShader("sprite");
	// 设置摄像机位置视角等
	MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);  
	Renderer = new SpriteRenderer(temp, MainCamera);

}
void Controller::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	// 鼠标移动可以移动视角
	if (this->State == ACTIVE)
	{
		MainCamera->ProcessMouseMovement(xoffset, yoffset, true);
	}
}

void Controller::Update(GLfloat dt)
{
	if (this->State == ACTIVE)
	{
	}
}


void Controller::ProcessInput(GLfloat dt)
{
	if (this->State == ACTIVE)
	{
	
	}
}

void Controller::Render(float rotateRad)
{
	if (this->State == ACTIVE)
	{
		// 进行点和线的渲染
		for (int i = 0; i < userPoint.size(); i++)
		{
			Renderer->DrawPoint(glm::vec3(userPoint[i].x, userPoint[i].y, 0), bigPointSize);
		}
		if (userPoint.size() > 1)
		{
			for (int i = 0; i < userPoint.size() - 1; i++)
			{
				Renderer->DrawLine(userPoint[i], userPoint[i + 1]);
			}
			for (int i = 0; i < curvePoint.size() - 1; i++)
			{
				Renderer->DrawLine(curvePoint[i], curvePoint[i + 1]);
			}
		}
	}
}

void Controller::AddUserPoint(float posX, float posY)
{
	// 添加一个新的用户点击的点
	glm::vec2 newPoint = glm::vec2(posX, posY);
	userPoint.push_back(newPoint);

	std::vector<glm::vec2>().swap(curvePoint);
	// 并且计算Bezier曲线
	if (userPoint.size() > 1)
	{
		for (double t = 0.0; t <= 1.0; t += 0.01)
		{
			float posX = 0;
			float posY = 0;
			for (int i = 0; i < userPoint.size(); i++)
			{
				posX += userPoint[i].x * countBernstein(i, userPoint.size() - 1, t);
				posY += userPoint[i].y * countBernstein(i, userPoint.size() - 1, t);
			}
			glm::vec2 newPoint = glm::vec2(posX, posY);
			// 添加到要渲染的点中
			curvePoint.push_back(newPoint);
		}
	}
}
void Controller::DeleteUserPoint()
{
	// 删除用户的点
	if (userPoint.size() != 0)
	{
		userPoint.pop_back();
	}
	std::vector<glm::vec2>().swap(curvePoint);
	// 重新计算Bezier曲线
	if (userPoint.size() > 1)
	{
		for (double t = 0.0; t <= 1.0; t += 0.01)
		{
			float posX = 0;
			float posY = 0;
			for (int i = 0; i < userPoint.size(); i++)
			{
				posX += userPoint[i].x * countBernstein(i, userPoint.size() - 1, t);
				posY += userPoint[i].y * countBernstein(i, userPoint.size() - 1, t);
			}
			glm::vec2 newPoint = glm::vec2(posX, posY);
			curvePoint.push_back(newPoint);
		}
	}
}

float Controller::countBernstein(int i, int n, float t)
{
	float B;
	if (i == 0 || n - i == 0)
	{
		B = 1;
	}
	else
	{
		B = Factorial(n) / (float)(Factorial(i) * Factorial(n - i));
	}
	B = B * pow(t, i) * pow(1 - t, n - i);
	return B;
}

float Controller::Factorial(int x)
{
	int ans = 1;
	for (int i = 1; i <= x; i++)
	{
		ans *= i;
	}
	return ans;
}