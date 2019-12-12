//
//  Light.cpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/12/12.
//  Copyright © 2019 陈霄. All rights reserved.
//

#include "Light.hpp"

Light::Light() {
    colour = glm::vec3(1.f, 1.f, 1.f);
    ambitionIntensity = 1.f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity = 1.f) {
    colour = glm::vec3(red, green, blue);
    ambitionIntensity = aIntensity;
}

Light::~Light() {
    
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation) {
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambitionIntensity, ambitionIntensity);
}
