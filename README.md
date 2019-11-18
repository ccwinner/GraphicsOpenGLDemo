# OpenGLDemoUdemy
学习Udemy上的现代OpenGL课程，原教程是在win上开发，这里迁移到macOS上，做了适当调整。

## mac配置指南

- blew install glew
- blew install glfw
- blew install glm, or Download glm from webpage.

- 修改header search path和library search path
- build phase里添加 OpenGL, 下载的glfw, glew.
- 修改scheme->options里的自定义工作目录为自己项目的地址

<font color=blue>项目中导入头文件#include<OpenGL/gl3.h>，苹果对glew做了定制，所以直接使用glew的内容会有不兼容的问题。</font>
