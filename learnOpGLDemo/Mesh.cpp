//
//  Mesh.cpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/15.
//  Copyright © 2019 陈霄. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}
/*
 着色器中两种值形式：
 1. 统一变量 uniform type variable
 2. 属性 attribute type variable
 获取方式都要：
 1. glGetUniformLocation or glGetAttributeLocation 获取位置id
    1.1. gl3以后可以通过layout(location=x)来直接指定属性的位置
    1.2. glVertexAttribPointer 指定顶点数组中每个顶点的属性
 2. glUniformXX or glVertexAttributeXX来给变量赋值, 带上位置id
 */

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
    indexCount = numOfIndices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
    if (IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}


Mesh::~Mesh()
{
    ClearMesh();
}
