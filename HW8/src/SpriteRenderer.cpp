#include "SpriteRenderer.h"
#include <iostream>


SpriteRenderer::SpriteRenderer(Shader *shader, Camera* camera)
{
	this->shader = shader;
	this->camera = camera;
	// ��ʼ��
	this->initPointData();
	this->initRenderLine();
}
void SpriteRenderer::DrawLine(glm::vec2 point1, glm::vec2 point2)
{
	this->shader->Use();
	// ���������˵�λ�ã�Ȼ������ߵ���Ⱦ
	float vertices[] = {
		// λ��                        
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
	// ���ù۲����
	glm::mat4 view = camera->GetViewMatrix();
	this->shader->SetMatrix4("view", view);
	// ����͸�Ӿ���
	glm::mat4 projection = glm::ortho(0.0f, 10.0f, 0.0f, 10.0f, 0.1f, 100.0f);
	this->shader->SetMatrix4("projection", projection);
	// ��Ⱦ
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	this->shader->SetMatrix4("model", model);
	// ���õ�Ĵ�С
	glPointSize(point_size);
	glBindVertexArray(pointVAO);
	glDrawArrays(GL_POINTS, 0, 1);
}
void SpriteRenderer::initPointData()
{
	float vertices[] = {
		// λ��                        
		0.0f,  0.0f,  0.0f,  0.458f, 0.663f, 0.71f,
	};
	// ����ƽ���VAO��VBO
	unsigned int planeVBO;
	glGenVertexArrays(1, &this->pointVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(this->pointVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	// λ�����Ժ���ɫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void SpriteRenderer::initRenderLine()
{

	float vertices[] = {
		// λ��                        
		0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	};
	unsigned int planeVBO;
	// ����ƽ���VAO��VBO
	glGenVertexArrays(1, &this->lineVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(this->lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	// λ�����Ժ���ɫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
