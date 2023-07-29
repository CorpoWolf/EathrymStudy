#include "cube.h"

GLuint initCube() 
{
    // Positions and colors for a cube
    float vertices[] = {
        // positions       // colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // front bottom-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // front bottom-right
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // front top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // front top-left

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // back bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // back bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // back top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f  // back top-left
    };

    unsigned int indices[] = {
        0, 1, 2, // front face
        2, 3, 0,
        1, 5, 6, // right face
        6, 2, 1,
        5, 4, 7, // back face
        7, 6, 5,
        4, 0, 3, // left face
        3, 7, 4,
        3, 2, 6, // top face
        6, 7, 3,
        4, 5, 1, // bottom face
        1, 0, 4
    };

    GLuint VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    return VAO;
}
