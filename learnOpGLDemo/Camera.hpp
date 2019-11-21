//
//  Camera.hpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/21.
//  Copyright © 2019 陈霄. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;//和up有区别，类似人行走方向与头的方向不一定一致。
    
    GLfloat yaw;
    GLfloat pitch;
    
    GLfloat moveSpeed;
    GLfloat turnSpeed;
    
    void update();
    
public:
    //position of camera based on world-axis.
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed);
    Camera();
    void keyControl(bool* keys, GLfloat deltaTime);
    glm::mat4 getViewMatrix();
    ~Camera();
};
