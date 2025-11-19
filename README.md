# 我的图形学笔记*Part1*
## 写在题前

本**Repository**意在为图书***Computer Graprics Programming(in OpenGL with C++)***, *written by V.S.Gordon and John Clevenger*提供书中的示例代码以及课后习题的代码实现

由于个人语言问题，本**Repository**目前是***Chinese-friendly***, 在我语言能力有所提升后，或许会尝试将代码中的注释以**英文**书写。

## 项目结构

**Repository**中包含了运行**OpenGL**所需要的代码环境:

1.**GLFW**:全称*Graphics Library Framework*,主要功能为创建窗口（window）,创建OpenGL上下文（context）以便窗口运行以及处理键鼠指令。在本**Repository**中存储在文件夹“GLFW_DEPENDENCIES”中。

2.**GLEW**:全称*OpenGL Extension Library*,主要功能是提供现代OpenGL函数，与一系列扩展。在本**Repository**中存储在文件夹“GLEW_DEPENDENCIES”中。

3.**SOIL2**:是OpenGL中常用的纹理加载器，常用于加载图片并把它转化为像素数据。在本**Repository**中存储在文件夹“soil2”中。

4.**GLM**:是OpenGL的数学库，提供矩阵，向量等数学运算。在本**Repository**中存储在文件夹“glm”中。

在本**Repository**中已经为读者汇总了所需的所有头文件，存储在文件夹“OpenGLtemplate”中。
