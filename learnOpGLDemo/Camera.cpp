//
//  Camera.cpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/21.
//  Copyright © 2019 陈霄. All rights reserved.
//

#include "Camera.hpp"
#include <GLFW/glfw3.h>

Camera::Camera() {
    
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed = 0.f, GLfloat startTurnSpeed = 0.f) {
    //相机的这一套坐标基于世界坐标系
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    moveSpeed = startMovementSpeed;
    turnSpeed = startTurnSpeed;
    
    update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {
    //类似Unity的移动计算函数 乘以deltaTime
    GLfloat velocity = moveSpeed * deltaTime;
    
    if (keys[GLFW_KEY_W]) {
        position += front * velocity;
    } else if (keys[GLFW_KEY_S]) {
        position -= front * velocity;
    } else if (keys[GLFW_KEY_A]) {
        position -= right * velocity;
    } else if (keys[GLFW_KEY_D]) {
        position += right * velocity;
    }
}

glm::mat4 Camera::getViewMatrix() {
    //lookAt输入参数：照相机位置，目标物体位置，up向量(不是worldUp)
    return glm::lookAt(position, position + front, up);
    //test
//    return glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
//    glm::vec3(0.0f, 0.0f, 0.0f),
//    glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::update() {
    //front指照相机的方向
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    
  //right和up向量的计算参考：https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/
    //worldUp一般是(0,1,0)
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera() {
    
}
