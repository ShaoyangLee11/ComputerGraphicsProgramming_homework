# 我的图形学笔记*Part1*
## 写在题前

本**Repository**意在为图书***Computer Graprics Programming(in OpenGL with C++)***, *written by V.S.Gordon and John Clevenger*提供书中的示例代码以及课后习题的代码实现，在我阅读与实现的过程中，会试图写下一些注释以便我自己与读者更好理解运行的过程。

由于个人英语能力有限，本**Repository**目前是***Chinese-friendly***, 在我语言能力有所提升后，或许会尝试将代码中的注释以**英文**书写。

## 项目结构

**Repository**中包含了运行**OpenGL**所需要的代码环境:
<br>

1.**GLFW**:全称 *Graphics Library Framework*,主要功能为创建窗口（window）,创建OpenGL上下文（context）以便窗口运行以及处理键鼠指令。在本**Repository**中存储在文件夹“GLFW_DEPENDENCIES”中。

2.**GLEW**:全称 *OpenGL Extension Library*,主要功能是提供现代OpenGL函数，与一系列扩展。在本**Repository**中存储在文件夹“GLEW_DEPENDENCIES”中。

3.**SOIL2**:是OpenGL中常用的纹理加载器，常用于加载图片并把它转化为像素数据。在本**Repository**中存储在文件夹“soil2”中。

4.**GLM**:是OpenGL的数学库，提供矩阵，向量等数学运算。在本**Repository**中存储在文件夹“glm”中。

在本**Repository**中已经为读者汇总了所需的所有头文件，存储在文件夹“OpenGLtemplate”中，读者可以自取。

5.**Nsight**配置：

## 笔记汇总

### 2.1.0:

<br>

*1.Pipline*

|*Shader(依照管线顺序)*|作用|
|---|---|
|1.顶点着色器(*Vertex Shader*)|进行顶点处理|
|2.曲面细分着色器(*Tessellation Shader*)|进行图元（如三角形）处理|
|3.几何着色器(*Geometry Shader*)|进行图元处理|
|4.光栅化(*Rasteration*)|将*fragment*转化为像素|
|5.片段着色器(*Fragment Shader*)|给转化后的像素赋予颜色|
|6.像素操作等|隐藏面消除等|

（上图中的蓝色部分是我们可以自定义的部分）

*2.GLuint数据类型*

GLuint是OpenGL当中的一种无符号整数类型，。在OpenGL中，所有的对象并不以 “对象” 的形式存储，而是以**对象ID**的形式存储（例如VAO,VBO,程序对象以及着色器等）。

![坐标实例](https://learnopengl-cn.github.io/img/01/04/ndc.png)

### 2.1.1：

<br>

*1. 什么是上下文(Context)?*

“上下文”（Context）是指 OpenGL 所有状态信息的集合。你可以把它理解为 OpenGL 的“工作环境”或“状态机”，它记录了当前所有的渲染设置、资源（如纹理、缓冲区对象、着色器等）以及与窗口系统的关联。

在本例中，函数 **glfwCreateWindow(600, 600, "Chapter2-Program1", NULL,NULL)** 为窗口对象window1设置了他自己的context,之后我们又使用函数 **glfwMakeContextCurrent(window1)** 将我们当前要使用的context设置为窗口对象**window1** 的context。

同时还要声明一点，OpenGL是***基于当前上下文的API***。如果更换上下文，那么之前绑定在当前上下文当中的VAO与VBO等都不再可用。


*2. 清除色(Clear Color)*

是指在**清除颜色缓冲区（通常是屏幕或帧缓冲）时所填充的颜色**。也就是说，每次调用 **glClear(GL_COLOR_BUFFER_BIT)** 时，OpenGL 会用你设置的清除色把整个颜色缓冲区填满。可以这样形象地理解：清除色就是“擦黑板”时用的颜色。每次开始新一帧渲染时，先用清除色把画布涂满，然后再绘制新的内容。
<br>

*3.顶点输入*

OpenGL仅当3D坐标在3个轴（x、y和z）上 **-1.0**到 **1.0**的范围内时才处理它。所有在这个范围内的坐标叫做**标准化设备坐标(Normalized Device Coordinates)**，此范围内的坐标最终显示在屏幕上 ***（在这个范围以外的坐标则不会显示）***。

![管线实例](https://learnopengl-cn.github.io/img/01/04/pipeline.png)

### 2.1.2：
<br>

*1. Vertex Array Object(VAO) & Vertex Buffer Object(VBO)*

VBO，译作顶点缓冲对象，用于存储顶点的数据（坐标，法线，纹理贴图等）

VAO，译作顶点数组对象，用于告诉GPU以什么样的顺序和方式读取VBO中的数据



*2. Shader的创建*

|步骤|（以顶点着色器为例）|
|---|---|
|1.导入顶点着色器源码|实质上是创建了一个字符串数组 **vShaderSource** 去暂时存储这段源码|
|2.创建顶点着色器对象|利用函数 *glCreateShader(GL_VERTEX_SHADER)* 创建名为 **vShader** 的着色器对象，数据类型为**GLuint**<br>其中函数传入的参数为**enum**类型，代表顶点着色器|
|3.把着色器源码附加到着色器对象上|新创建的着色器对象并不附带任何源码<br>利用函数 *glShaderSource(vShader, 1, &vShaderSource, NULL)* 把着色器源码附加到着色器对象上|
|4.编译顶点着色器|附着时，OpenGL 只是把你的 GLSL 源码（字符串）存储到着色器对象里，还没有把它变成可以在 GPU 上运行的机器代码。<br>只有调用 glCompileShader 编译后，OpenGL 才会把 GLSL 源码翻译成 GPU 能理解和执行的代码。这样 GPU 才能用你的着色器进行渲染。|
|5.创建程序对象|*GLuint vfProgram = glCreateProgram();*|
|6.把所有创建的着色器对象附加到程序对象上|*glAttachShader(vfProgram, vShader);*|
|7.链接（link）程序对象|*glLinkProgram(vfProgram);*|



*3. Program Object (程序对象)*

在 OpenGL 里，程序对象是用来管理和执行着色器的容器。它是 GPU 端的一个对象，里面装着已经编译好的着色器（如顶点着色器、片元着色器等），并把它们链接（link）在一起，最终形成一个可运行的 GPU 程序。

程序对象（Program Object）的作用是把多个着色器（如顶点着色器和片段着色器）组合在一起，形成一个完整的渲染管线阶段。

单独的着色器（比如顶点着色器或片段着色器）只是渲染流程中的一部分，不能独立工作。只有把它们组合起来，才能完成一次完整的渲染。

**流程**：你需要用 glCreateProgram 创建一个程序对象，然后用 glAttachShader 把编译好的着色器对象附加到程序对象上。最后用 glLinkProgram 把这些着色器链接成一个可以在GPU上运行的“程序”。

程序对象让你可以方便地管理和切换不同的着色器组合。例如，你可以有多个程序对象，每个对象对应不同的渲染效果。

### 2.3

（在此提醒一下读者，2.3并不代表书中的“程序2.3”，而是代表**第2章第3小节**下附属的代码）

在2.3中，我们不再使用直接通过字符串数组去承载*Shader*的源码，而是定义了函数 *readShaderSource()* 来接收源码，函数代码如下：

```
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
```

### 2.5

*1.Uniform类型*

在 OpenGL 的 GLSL里，*uniform* 变量是一种 从 **CPU（你的 C++ 代码）传递到 GPU 着色器 的变量**，并且在一次 *draw call*（一次绘制过程）中保持不变。

|特点|例子|
|---|---|
|1.由 CPU 设置（glUniform 系列函数）|你必须在 C++/OpenGL 里写：<br> *glUniform1f(loc, 1.0f);* <br>shader 本身不能修改它。|
|2.对所有着色器阶段都是“全局”可见的|它不是“顶点独享”或“片元独享”的，而是可以让 shader pipeline 中所有阶段共享。|
|3.在一次 draw call 内保持不变|例如：<br>*glDrawArrays(...);* <br>在这一条绘制命令里，uniform 对所有顶点和所有像素都是一样的。<br>如果你要改变它，必须：<br>*glUniform1f(loc, newValue);* <br>*glDrawArrays(...)*   // 此时才生效|

传统使用方式（也是本书当中提供的例子）：
```

GLuint prog = ...;
glUseProgram(prog);

GLint loc = glGetUniformLocation(prog, "u_time");
glUniform1f(loc, 3.14f);

```

利用函数*glGetUniformLocation(...)* 返回 uniform 在 shader 程序中的位置（也叫做ID）

再利用*glUniform1f(...)* 向 uniform 传值。

### 第2章习题解析：




