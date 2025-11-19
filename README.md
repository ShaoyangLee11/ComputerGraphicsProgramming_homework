# 我的图形学笔记*Part1*
## 写在题前

本**Repository**意在为图书***Computer Graprics Programming(in OpenGL with C++)***, *written by V.S.Gordon and John Clevenger*提供书中的示例代码以及课后习题的代码实现，在我阅读与实现的过程中，会试图写下一些注释以便我自己与读者更好理解运行的过程。

由于个人英语能力有限，本**Repository**目前是***Chinese-friendly***, 在我语言能力有所提升后，或许会尝试将代码中的注释以**英文**书写。

## 项目结构

**Repository**中包含了运行**OpenGL**所需要的代码环境:

1.**GLFW**:全称*Graphics Library Framework*,主要功能为创建窗口（window）,创建OpenGL上下文（context）以便窗口运行以及处理键鼠指令。在本**Repository**中存储在文件夹“GLFW_DEPENDENCIES”中。

2.**GLEW**:全称*OpenGL Extension Library*,主要功能是提供现代OpenGL函数，与一系列扩展。在本**Repository**中存储在文件夹“GLEW_DEPENDENCIES”中。

3.**SOIL2**:是OpenGL中常用的纹理加载器，常用于加载图片并把它转化为像素数据。在本**Repository**中存储在文件夹“soil2”中。

4.**GLM**:是OpenGL的数学库，提供矩阵，向量等数学运算。在本**Repository**中存储在文件夹“glm”中。

在本**Repository**中已经为读者汇总了所需的所有头文件，存储在文件夹“OpenGLtemplate”中，读者可以自取。

## 笔记的汇总

### 2.1.1：

1.什么是上下文(Context)?

“上下文”（Context）是指 OpenGL 所有状态信息的集合。你可以把它理解为 OpenGL 的“工作环境”或“状态机”，它记录了当前所有的渲染设置、资源（如纹理、缓冲区对象、着色器等）以及与窗口系统的关联。

在本例中，函数**glfwCreateWindow(600, 600, "Chapter2-Program1", NULL,NULL)** 为窗口对象window1设置了他自己的context,之后我们又使用函数**glfwMakeContextCurrent(window1)** 将我们当前要使用的context设置为窗口对象**window1** 的context。

同时还要声明一点，OpenGL是***基于当前上下文的API***。如果更换上下文，那么之前绑定在当前上下文当中的VAO与VBO等都不再可用。
