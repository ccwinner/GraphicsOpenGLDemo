//
//  Window.cpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/15.
//  Copyright © 2019 陈霄. All rights reserved.
//

#include "Window.hpp"

Window::Window()
{
    width = 800;
    height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;
}

int Window::Initialise()
{
    if (!glfwInit())
    {
        printf("Error Initialising GLFW");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW Windows Properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatiblity
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        printf("Error creating GLFW window!");
        glfwTerminate();
        return 1;
    }

    // Get buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set the current context
    glfwMakeContextCurrent(mainWindow);

    //callbacks
    createCallbacks();
    //禁用鼠标的移动，但是回调还能执行
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Allow modern extension access
    // on Mac, disable this feature
//    glewExperimental = GL_TRUE;

//    GLenum error = glewInit();
//    if (error != GLEW_OK)
//    {
//        printf("Error: %s", glewGetErrorString(error));
//        glfwDestroyWindow(mainWindow);
//        glfwTerminate();
//        return 1;
//    }
    //开启深度测试，否则展示的三维物体没有质感.
    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    // 注册一个窗口动作的回调之前，设置回调使用到的数据（第二个参数）
    // 可以通过glfwGetWindowUserPointer来获取设置的数据.
    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}


Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

void Window::createCallbacks() {
    glfwSetKeyCallback(this->mainWindow, handleKeys);
    glfwSetCursorPosCallback(this->mainWindow, handleMouse);
}

//回调函数
void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (GLFW_KEY_ESCAPE == key && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
//            printf("press valid key:%d\n",key);
        }
        else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
//            printf("release valid key:%d\n",key);
        }
    }
}

void Window::handleMouse(GLFWwindow *window, double xPos, double yPos) {
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (theWindow->mouseFirstMoved) {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }
    theWindow->xChange = xPos - theWindow->lastX;
    //为了不颠倒方向吧。。
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastY = xPos; theWindow->lastX = xPos;
    /**
     以mainWindow的左上角为原点（0,0)了。和设备坐标系一致。
     */
//    printf("x:%.6f,y:%.6f\n", xPos, yPos);
}

GLfloat Window::getXChange() {
    GLfloat res = this->xChange;
    this->xChange = 0.0f;
    return res;
}

GLfloat Window::getYChange() {
    GLfloat res = this->yChange;
    this->yChange = 0.0f;
    return res;
}
