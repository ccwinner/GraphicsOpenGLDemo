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
    
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);
    ~Light();
};
