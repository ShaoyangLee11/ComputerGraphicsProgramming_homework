#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

using namespace std;

//本题只提供代码框架，有些函数并未写完整是因为在此题中没有用到

void init(GLFWwindow* window){}

void display(GLFWwindow* window, double currentTime) {
	glClearColor(1.0, 0.0, 0.0, 1.0);//指定清除背景时所用的颜色（可以理解为一种名为“清除色（clear color）”的颜色），这里使用红色
	glClear(GL_COLOR_BUFFER_BIT);//清理颜色缓冲区中的数据，并用红色填充颜色缓冲区
}

int main(){
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