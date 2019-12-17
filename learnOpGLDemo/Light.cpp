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
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity) {
    colour = glm::vec3(red, green, blue);
    ambitionIntensity = aIntensity;

    direction = glm::vec3(xDir, yDir, zDir);
    diffuseIntensity = dIntensity;
}

Light::~Light() {
    
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation) {
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambitionIntensity, ambitionIntensity);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
