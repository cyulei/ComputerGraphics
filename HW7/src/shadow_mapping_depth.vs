#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    // 把顶点变换到光空间
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}