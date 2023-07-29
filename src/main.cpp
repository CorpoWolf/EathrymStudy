#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include "cube.h"
#include "shader.h"
#include "GLM/glm.hpp"                  // glm::vec3, glm::mat4
#include "GLM/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "GLM/gtc/type_ptr.hpp"         // glm::value_ptr

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // Initialize and configure GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    // Create a window
    int windowWidth = 800, windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Load the shader program
    GLuint shaderProgram = LoadShaders("../src/shaders/Vshade.vert", "../src/shaders/Fshade.frag");
    if (shaderProgram == 0) 
    {
        std::cout << "Failed to load shaders" << std::endl;
        return -1;
    }

    // Initialize the cube
    GLuint cubeVAO = initCube();
    if (cubeVAO == 0) 
    {
        std::cout << "Failed to initialize cube" << std::endl;
        return -1;
    }
    
    float startTime = glfwGetTime();

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Calculate time
        float currentTime = glfwGetTime();
        float elapsedTime = currentTime - startTime;

        // Process input
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(80.0f), float(windowWidth / windowHeight), 0.1f, 100.0f);
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Set view matrix
        glm::vec3 cameraPos = glm::vec3(0.0f, -1.0f, 3.0f); // Camera Position
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Looking at the origin (where your cube is)
        glm::vec3 upVector = glm::vec3(0.0f, -1.0f, 0.0f); // "Up" is in the positive y direction
        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, upVector);
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Set model matrix with rotation based on elapsed time
        float rotationSpeed = 0.5f; // Adjust the rotation speed here
        float angle = rotationSpeed * elapsedTime; // Calculate the angle based on time
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

        // Send the matrices to the shader
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        // Draw the cube
        glUseProgram(shaderProgram);
        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Terminate GLFW
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
