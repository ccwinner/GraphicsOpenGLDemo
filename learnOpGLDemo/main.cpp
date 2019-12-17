//
//  main.cpp
//  learnOpGLDemo
//
//  Created by chenxiao on 2019/11/9.
//  Copyright © 2019 陈霄. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Light.hpp"

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Texture brickTex, dirtTex;

Light mainLight;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
// Vertex Shader
static const char* vShader = "./Resource/shader.vert";

// Fragment Shader
static const char* fShader = "./Resource/shader.frag";

void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
                        unsigned int vLength, unsigned int normalOffset)
{
    for (size_t i = 0; i < indiceCount; i += 3)
    {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);
        
        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    //x,y,z,u,v
    //u和v可以超过0到1的范围，超过以后出发wrapper配置的效果
    GLfloat vertices[] = {
        //x,y,z  u,v,  nx,ny,nz
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f
    };
    //计算出每个顶点的法线（均值）
    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
    
    Mesh *obj1 = new Mesh();
    //包含完整的vertices
    obj1->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);
}

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

void CreateTextures() {
    brickTex = Texture("./Resource/brick.png");
    brickTex.loadTexture();
    dirtTex = Texture("./Resource/dirt.png");
    dirtTex.loadTexture();
}

void CreateCamera() {
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.5f);
}

void CreateLight() {
    mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f,
    2.0f, -1.0f, -2.0f, 1.0f);;
}

int main()
{

    mainWindow = Window(800, 600);
    mainWindow.Initialise();

    CreateObjects();
    CreateShaders();
    CreateTextures();
    CreateCamera();
    CreateLight();

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    GLuint uniformAmbientColour = 0, uniformAmbientIntensity = 0, uniformDirection = 0, uniformDiffuseIntensity = 0;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

    // Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
        deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
        lastTime = now;
        
        // Get + Handle User Input
        glfwPollEvents();
        
        //有点类似Unity的在Update回调里加入键盘操作的逻辑了
        camera.keyControl(mainWindow.getsKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        // Clear the window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();

        uniformModel = shaderList.front().GetModelLocation();
        uniformProjection = shaderList.front().GetProjectionLocation();
        uniformView = shaderList.front().GetViewLocation();
        uniformAmbientIntensity = shaderList.front().GetAmbientIntensityLocation();
        uniformAmbientColour = shaderList.front().GetAmbientColourLocation();
        uniformDirection = shaderList.front().GetDirectionLocation();
        uniformDiffuseIntensity = shaderList.front().GetDiffuseIntensityLocation();
        
        mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour,
        uniformDiffuseIntensity, uniformDirection);
        
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        brickTex.useTexture();
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        dirtTex.useTexture();
        meshList[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}

