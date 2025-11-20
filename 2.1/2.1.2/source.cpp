#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

#define numVAOs 1//VAO全称Vertex Array Object,顶点数组对象

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {
	// Placeholder for shader creation logic
	const char* vShaderSource = "#version 430 core\n"
								"void main()\n" 
								"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";//这一行就是顶点着色器的源码
	
	const char* fShaderSource = "#version 430 core\n"
								"out vec4 color;\n"
								"void main()"
								"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";//这一段就是片段着色器的源码

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);//这里创建了顶点着色器对象，返回一个整数ID作为后边引用它的序号，但这个对象本身还没有任何实际的着色器代码。
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);//这里创建了片段着色器对象，返回一个整数ID作为后边引用它的序号，但这个对象本身还没有任何实际的着色器代码。

	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glShaderSource(fShader, 1, &fShaderSource, NULL);//把着色器源码附加到着色器对象上
	
	glCompileShader(vShader);//编译顶点着色器，相当于将字符串数组转成源码（或者叫机器码）。
	glCompileShader(fShader);//编译片段着色器

	/*为什么还要对着色器进行编译？
	附着时，OpenGL 只是把你的 GLSL 源码（字符串）存储到着色器对象里，还没有把它变成可以在 GPU 上运行的机器代码。
	只有调用 glCompileShader 编译后，OpenGL 才会把 GLSL 源码翻译成 GPU 能理解和执行的代码。这样 GPU 才能用你的着色器进行渲染。*/

	GLuint vfProgram = glCreateProgram();//创建一个程序对象
	glAttachShader(vfProgram, vShader);//把顶点着色器附加到程序对象上
	glAttachShader(vfProgram, fShader);//把片段着色器附加到程序对象上
	glLinkProgram(vfProgram);//链接程序对象


	/*程序对象（Program Object）的作用是把多个着色器（如顶点着色器和片段着色器）组合在一起，形成一个完整的渲染管线阶段。原因如下：
	1.	单个着色器不完整
	单独的着色器（比如顶点着色器或片段着色器）只是渲染流程中的一部分，不能独立工作。只有把它们组合起来，才能完成一次完整的渲染。
	2.	程序对象负责链接
	你需要用 glCreateProgram 创建一个程序对象，然后用 glAttachShader 把编译好的着色器对象附加到程序对象上。最后用 glLinkProgram 把这些着色器链接成一个可以在GPU上运行的“程序”。
	3.	便于管理和切换
	程序对象让你可以方便地管理和切换不同的着色器组合。例如，你可以有多个程序对象，每个对象对应不同的渲染效果。*/
	
	return vfProgram;
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);//生成一个顶点数组对象
	glBindVertexArray(vao[0]);//绑定顶点数组对象
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲区

	glUseProgram(renderingProgram);//使用着色器程序对象

	glPointSize(30.0f);//设置点的大小

	glDrawArrays(GL_POINTS, 0, 1);//绘制图元，这里绘制一个点。本函数的作用是启动整个管线过程
}

using namespace std;

int main() {
		//GLFW_part
	if (!glfwInit()) { exit(EXIT_FAILURE); }//初始化失败直接exit
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//指定GLFW的版本
	GLFWwindow* window1 = glfwCreateWindow(600, 600, "Chapter2-Program1", NULL,NULL);//创建这个window的OpenGL属性（也称作Context,上下文）
	glfwMakeContextCurrent(window1);//将新创建的窗口window1的上下文设置为你当前使用的上下文，window1的context不会当前你要使用的context自动关联，必须调用此函数!

	//GLEW_part
	if(glewInit()!=GLEW_OK){ exit(EXIT_FAILURE); }
	glfwSwapInterval(1);//开启垂直同步，防止撕帧

	init(window1);

	while (!glfwWindowShouldClose(window1)) {//检测窗口关闭事件
		display(window1, glfwGetTime());//glfwGetTime会返回GLFW初始化之后经过的时间
		glfwSwapBuffers(window1);//交换缓冲区
		glfwPollEvents();
	}

	glfwDestroyWindow(window1);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}