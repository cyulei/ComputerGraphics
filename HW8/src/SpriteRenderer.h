#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Camera.h"
class SpriteRenderer
{
public:
	SpriteRenderer(Shader *shader, Camera* camera);

	void DrawPoint(glm::vec3 position, float point_size);
	void DrawLine(glm::vec2 point1, glm::vec2 point2);
	
private:
	Shader* shader;
	Camera* camera;
	// ��Ҫ��Ⱦ��VAO
	GLuint pointVAO;
	GLuint lineVAO;
	// ��ʼ����Ⱦ�����VAO,VBO
	void initPointData();
	void initRenderLine();
};


#endif