#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

string readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);

	if (!fileStream.is_open()) {
		cerr << "Could not read file " << filePath << ". File does not exist." << endl;
		return "";
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint createShaderProgram() {

	string vShaderStr = readShaderSource("vertShader.glsl");
	string fShaderStr = readShaderSource("fragShader.glsl");

	const char* vShaderSource = vShaderStr.c_str();

	const char* fShaderSource = fShaderStr.c_str();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glShaderSource(fShader, 1, &fShaderSource, NULL);//把着色器源码附加到着色器对象上

	glCompileShader(vShader);
	glCompileShader(fShader);


	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

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

	glDrawArrays(GL_POINTS, 0, 1);//绘制图元，这里绘制一个点
}

using namespace std;

int main() {
	//GLFW_part
	if (!glfwInit()) { exit(EXIT_FAILURE); }//初始化失败直接exit
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//指定GLFW的版本
	GLFWwindow* window1 = glfwCreateWindow(600, 600, "Chapter2-Program1", NULL, NULL);//创建这个window的OpenGL属性（也称作Context,上下文）
	glfwMakeContextCurrent(window1);//将新创建的窗口window1的上下文设置为你当前使用的上下文，window1的context不会当前你要使用的context自动关联，必须调用此函数!

	//GLEW_part
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
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