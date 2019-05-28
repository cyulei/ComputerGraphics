#include <iostream>
#include <string>  
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "Controller.h"
#include "ResourceManager.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 处理用户的输入域
void processInput(GLFWwindow* window);
// 处理鼠标点击事件
void mousepress_callback(GLFWwindow* window, int button, int action, int mods);
// 处理鼠标移动事件
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool isLockView = false;

// 第一次窗口出现鼠标
bool firstMouse = true;

const unsigned int SCR_WIDTH = 1200;                      //显示窗口宽度
const unsigned int SCR_HEIGHT = 900;                      //显示窗口高度

// 创建控制器
Controller controller(SCR_WIDTH, SCR_HEIGHT);

float mouseX;
float mouseY;

int main()
{
	//初始化glfw
	glfwInit();
	//配置版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	 //创建GLFW窗口
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

	// 初始化
	controller.Init();
	// 计算Update相隔时间
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	controller.State = ACTIVE;

	//渲染
	while (!glfwWindowShouldClose(window))
	{
		// 开启深度测试
		glEnable(GL_DEPTH_TEST);
		// 清空深度缓存
		glClear(GL_DEPTH_BUFFER_BIT);
		//处理用户输入
		processInput(window);


		// 计算每一次渲染相差的时间
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// 处理用户输入
		controller.ProcessInput(deltaTime);

		// 更新状态
		controller.Update(deltaTime);

		//设置清空屏幕所用的颜色
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//清除颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT);

		// 渲染
		controller.Render((float)glfwGetTime());

		//交换颜色缓冲
		glfwSwapBuffers(window);
		//检查IO事件
		glfwPollEvents();
	}
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	//释放资源
	glfwTerminate();

	return 0;
}

//处理所有的输入
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
		// 在左键按下的时候对鼠标位置进行转换，然后加入用户的点中
		float posX = mouseX / (float)120;
		float posY = (float)10 - mouseY / (float)90;
	
		controller.AddUserPoint(posX, posY);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		// 右键按下删除最后添加的点
		controller.DeleteUserPoint();
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// 更新鼠标的位置
	mouseX = xpos;
	mouseY = ypos;
}