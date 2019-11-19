//
//  Texture.cpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/19.
//  Copyright © 2019 陈霄. All rights reserved.
//
#define STB_IMAGE_IMPLEMENTATION

#include "Texture.hpp"

Texture::Texture() : textureID(0), width(0), height(0), bitDepth(0),filePath("")
{}

Texture::Texture(const char *filePath) {
    Texture();
    this->filePath = filePath;
}

void Texture::loadTexture() {
    unsigned char *textData = stbi_load(filePath, &width, &height, &bitDepth, 0);
    if (!textData) {
        printf("load textdata failed\n");
        return;
    }
    //生成纹理的完整过程
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    //set wrapper
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //set filter GL_TEXTURE_MIN_FILTER when become small
    //GL_TEXTURE_MAG_FILTER when become big
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);
    glGenerateMipmap(GL_TEXTURE_2D);
    //恢复上下文
    glBindTexture(GL_TEXTURE_2D, 0);
    //释放资源
    stbi_image_free(textData);
}

void Texture::useTexture() {
    //激活texture unit 0,默认是0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
    filePath = nullptr;
}

Texture::~Texture() {
    
}
