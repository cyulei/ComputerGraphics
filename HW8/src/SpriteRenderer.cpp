#include "SpriteRenderer.h"
#include <iostream>


SpriteRenderer::SpriteRenderer(Shader *shader, Camera* camera)
{
	this->shader = shader;
	this->camera = camera;
	// 初始化
	this->initPointData();
	this->initRenderLine();
}
void SpriteRenderer::DrawLine(glm::vec2 point1, glm::vec2 point2)
{
	this->shader->Use();
	// 输入两个端点位置，然后进行线的渲染
	float vertices[] = {
		// 位置                        
		point1.x, point1.y,  0.0f, 1.0f, 0.0f, 0.0f,
		point2.x, point2.y,  0.0f,  1.0f, 0.0f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glm::mat4 model = glm::mat4(1.0f);
	this->shader->SetMatrix4("model", model);
	
	glBindVertexArray(lineVAO);
	glDrawArrays(GL_LINES, 0, 2);
}
void SpriteRenderer::DrawPoint(glm::vec3 position, float point_size)
{
	this->shader->Use();
	// 设置观察矩阵
	glm::mat4 view = camera->GetViewMatrix();
	this->shader->SetMatrix4("view", view);
	// 设置透视矩阵
	glm::mat4 projection = glm::ortho(0.0f, 10.0f, 0.0f, 10.0f, 0.1f, 100.0f);
	this->shader->SetMatrix4("projection", projection);
	// 渲染
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	this->shader->SetMatrix4("model", model);
	// 设置点的大小
	glPointSize(point_size);
	glBindVertexArray(pointVAO);
	glDrawArrays(GL_POINTS, 0, 1);
}
void SpriteRenderer::initPointData()
{
	float vertices[] = {
		// 位置                        
		0.0f,  0.0f,  0.0f,  0.458f, 0.663f, 0.71f,
	};
	// 设置平面的VAO和VBO
	unsigned int planeVBO;
	glGenVertexArrays(1, &this->pointVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(this->pointVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	// 位置属性和颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void SpriteRenderer::initRenderLine()
{

	float vertices[] = {
		// 位置                        
		0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	};
	unsigned int planeVBO;
	// 设置平面的VAO和VBO
	glGenVertexArrays(1, &this->lineVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(this->lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	// 位置属性和颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
