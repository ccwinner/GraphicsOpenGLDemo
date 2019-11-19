//
//  Texture.hpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/19.
//  Copyright © 2019 陈霄. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <OpenGL/gl3.h>
#include "stb_image.h"

class Texture {
    GLuint textureID;
    int width, height, bitDepth;
    const char *filePath;
public:
    Texture();
    Texture(const char *filePath);
    
    void loadTexture();
    void useTexture();
    void clearTexture();
    
    ~Texture();
};


