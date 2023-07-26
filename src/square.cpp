#include "shader.h"
#include "square.h"

unsigned int hctVBO, hctVAO, hctEBO; 

void square() {
    float vertices[] = {
      -0.8f, -0.8f, 0.0f, 0.011764705882352941f, 0.2549019607843137f, 0.34901960784313724f,
       0.8f, -0.8f, 0.0f, 0.00784313725490196f, 0.34901960784313724f, 0.3176470588235294f,
       0.8f, 0.8f, 0.0f,  0.011764705882352941f, 0.5490196078431373f, 0.24313725490196078f,
      -0.8f, 0.8f, 0.0f,  0.011764705882352941f, 0.5490196078431373f, 0.24313725490196078f
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0 
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
      vaoBindingPoint,    // VAO Binding Point
      hctVBO,             // VBO Binding
      0,                  // Offset
      6*sizeof(float));   // stride

    glEnableVertexArrayAttrib(hctVAO, attribPos);
    glEnableVertexArrayAttrib(hctVAO, attribCol);
    glVertexArrayAttribFormat(hctVAO, attribPos, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribFormat(hctVAO, attribCol, 3, GL_FLOAT, false, 3*sizeof(float));

    //Explicit binding of an attribute to a vao binding point
    glVertexArrayAttribBinding(hctVAO, attribPos, vaoBindingPoint);
    glVertexArrayAttribBinding(hctVAO, attribCol, vaoBindingPoint);

    //Step 3: Create EBO
    glCreateBuffers(1, &hctEBO);
    glNamedBufferStorage(hctEBO, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);

    //Bind EBO to VAO
    glVertexArrayElementBuffer(hctVAO, hctEBO);

    const char* vertexShaderPath = "../src/shaders/Vshade.vert";
    const char* fragmentShaderPath = "../src/shaders/Fshade.frag";
    
    GLuint shaderProgram = LoadShaders(vertexShaderPath, fragmentShaderPath);
    glUseProgram(shaderProgram);
}
