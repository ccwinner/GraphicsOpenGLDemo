//
//  Light.hpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/12/12.
//  Copyright © 2019 陈霄. All rights reserved.
//
#pragma once

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

class Light {
    glm::vec3 colour;
    GLfloat ambitionIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
    
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    ~Light();
};
