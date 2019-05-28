#include <iostream>
#include <string>  
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "Controller.h"
#include "ResourceManager.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// �����û���������
void processInput(GLFWwindow* window);
// ����������¼�
void mousepress_callback(GLFWwindow* window, int button, int action, int mods);
// ��������ƶ��¼�
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool isLockView = false;

// ��һ�δ��ڳ������
bool firstMouse = true;

const unsigned int SCR_WIDTH = 1200;                      //��ʾ���ڿ��
const unsigned int SCR_HEIGHT = 900;                      //��ʾ���ڸ߶�

// ����������
Controller controller(SCR_WIDTH, SCR_HEIGHT);

float mouseX;
float mouseY;

int main()
{
	//��ʼ��glfw
	glfwInit();
	//���ð汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	 //����GLFW����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HW8", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mousepress_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	// ��ʼ��
	controller.Init();
	// ����Update���ʱ��
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	controller.State = ACTIVE;

	//��Ⱦ
	while (!glfwWindowShouldClose(window))
	{
		// ������Ȳ���
		glEnable(GL_DEPTH_TEST);
		// �����Ȼ���
		glClear(GL_DEPTH_BUFFER_BIT);
		//�����û�����
		processInput(window);


		// ����ÿһ����Ⱦ����ʱ��
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// �����û�����
		controller.ProcessInput(deltaTime);

		// ����״̬
		controller.Update(deltaTime);

		//���������Ļ���õ���ɫ
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//�����ɫ����
		glClear(GL_COLOR_BUFFER_BIT);

		// ��Ⱦ
		controller.Render((float)glfwGetTime());

		//������ɫ����
		glfwSwapBuffers(window);
		//���IO�¼�
		glfwPollEvents();
	}
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	//�ͷ���Դ
	glfwTerminate();

	return 0;
}

//�������е�����
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{

	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mousepress_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		// ��������µ�ʱ������λ�ý���ת����Ȼ������û��ĵ���
		float posX = mouseX / (float)120;
		float posY = (float)10 - mouseY / (float)90;
	
		controller.AddUserPoint(posX, posY);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		// �Ҽ�����ɾ�������ӵĵ�
		controller.DeleteUserPoint();
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// ��������λ��
	mouseX = xpos;
	mouseY = ypos;
}