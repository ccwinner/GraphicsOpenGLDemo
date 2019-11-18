//
//  Window.hpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/15.
//  Copyright © 2019 陈霄. All rights reserved.
//

#pragma once

#include "stdio.h"

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();

    Window(GLint windowWidth, GLint windowHeight);

    int Initialise();

    GLint getBufferWidth() { return bufferWidth; }
    GLint getBufferHeight() { return bufferHeight; }

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    ~Window();

private:
    GLFWwindow* mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;
};
