#include "shader.h"
#include "triangle.h"

unsigned int hctVBO;
unsigned int hctVAO;

void triangle() {
    float vertices[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
       0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    GLuint attribPos = 0;
    GLuint attribCol = 1;

    //Step 1: Create VBO
    glCreateBuffers(1, &hctVBO);
    glNamedBufferStorage(hctVBO, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

    //Step 2: Create VAO
    glCreateVertexArrays(1, &hctVAO);

    GLuint vaoBindingPoint = 0;
    glVertexArrayVertexBuffer(
      hctVAO,             // VAO Binding
      vaoBindingPoint,    // 
      hctVBO,             // VBO Binding
      0,                  // 
      6*sizeof(float));   // stride

    glEnableVertexArrayAttrib(hctVAO, attribPos);
    glEnableVertexArrayAttrib(hctVAO, attribCol);
    glVertexArrayAttribFormat(hctVAO, attribPos, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribFormat(hctVAO, attribCol, 3, GL_FLOAT, false, 3*sizeof(float));

    //Explicit binding of an attribute to a vao binding point
    glVertexArrayAttribBinding(hctVAO, attribPos, vaoBindingPoint);
    glVertexArrayAttribBinding(hctVAO, attribCol, vaoBindingPoint);

    const char* vertexShaderPath = "../src/shaders/Vshade.vert";
    const char* fragmentShaderPath = "../src/shaders/Fshade.frag";
    
    GLuint shaderProgram = LoadShaders(vertexShaderPath, fragmentShaderPath);
    glUseProgram(shaderProgram);
}

