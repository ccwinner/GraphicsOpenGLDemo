//
//  Mesh.hpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/15.
//  Copyright © 2019 陈霄. All rights reserved.
//

#pragma once

#include <OpenGL/gl3.h>

class Mesh {
public:
    Mesh();
    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();
    
    ~Mesh();
    
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};
