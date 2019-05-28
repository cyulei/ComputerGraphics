# Homework 8 - Bezier Curve

## 实现效果

![gif][2]

[2]: https://raw.githubusercontent.com/cyulei/ComputerGraphics/master/HW8/doc/pic/poin.gif



![gif2][3]

[3]: https://raw.githubusercontent.com/cyulei/ComputerGraphics/master/HW8/doc/pic/poin2.gif

## 实现思路

### 整体框架
#### 控制
> 控制类，主程序与渲染和资源的交互接口，可以处理用户的输入，实时渲染和更改渲染的顶点。通过该类主程序能够方便的去控制需要渲染的内容。
```c
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
```
#### 渲染
> 通过该类可以进行点或者线的渲染，包含一个shader，可以利用shader实时改变渲染的内容，定义了一个点的VAO以及线的VAO。控制类可以通过访问该类的方法来进行相应图形的渲染。
```c
class SpriteRenderer
{
public:
	SpriteRenderer(Shader *shader, Camera* camera);

	void DrawPoint(glm::vec3 position, float point_size);
	void DrawLine(glm::vec2 point1, glm::vec2 point2);
	
private:
	Shader* shader;
	Camera* camera;
	// 需要渲染的VAO
	GLuint pointVAO;
	GLuint lineVAO;
	// 初始化渲染对象的VAO,VBO
	void initPointData();
	void initRenderLine();
};
```
#### 加载资源
> 一个资源管理类，用于加载用户路径的shader
```c
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader*>    Shaders;

	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader *  LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	// Retrieves a stored sader
	static Shader *  GetShader(std::string name);

	// Properly de-allocates all loaded resources
	static void      Clear();
private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader  *  loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
};
```
### 鼠标点击
> 本次项目要求实现，鼠标点击的响应，在左键点击添加Bezier曲线的控制点，右键点击则对当前添加的最后一个控制点进行消除。其中还需要知道鼠标点击的位置，从而知道需要在哪里添加控制点。

当鼠标左键点击的时候，通过绑定回调函数，我们可以知道左键按下，因为同时绑定了一个鼠标移动的回调函数，于是知道鼠标的位置，但该鼠标的位置是相对于窗口的坐标，最左上角是(0,0)，最右下角是(窗口宽,窗口高)。而在世界坐标中，我使用的是正交投影，投影窗口大小是(0,10)(0,10)，因为窗口宽为1200，高为900，所以通过鼠标位置 / (窗口 / 10)，就可以变换到对应世界坐标的位置，然后又因为世界坐标中最左下角是(0,0)，所以y坐标的值要用10-刚才算出的值。

```c
// 处理鼠标点击事件
void mousepress_callback(GLFWwindow* window, int button, int action, int mods);
// 处理鼠标移动事件
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

glfwSetMouseButtonCallback(window, mousepress_callback);
glfwSetCursorPosCallback(window, mouse_callback);

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
```
### 计算Bezier曲线
> 计算Bezier曲线根据其公式，可以算出曲线上的每一个点，然后将每一个点依次连接，最后得到的结果就类似于一条曲线

![公式图][1]


[1]: https://raw.githubusercontent.com/cyulei/ComputerGraphics/master/HW8/doc/pic/curve.JPG

```c
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
```
### 实时更新
> 要求在添加控制点或删除控制点后，对曲线进行更新，意思就是在相应的鼠标事件发生的时候，重新计算曲线的点。

在本次项目中我使用vector去存储用户的控制点以及Bezier曲线上的各点
```c
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
```
## 总结
本次项目对之前项目进行一些重构，增加了控制类，使得主程序与渲染和加载资源分离开，在计算Bezier曲线的时候，很容易忽略，0的阶乘与0作为除数的情况导致计算错误，根据t的增量值，增量值越小，那么结果就越接近于一条真实的曲线。