#include "../include/glad/glad.h"
#include "../include/InitOpenGL.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Shader.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

// Process Input
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    GLFWwindow *window = initOpenGL(600, 600, 3, 3);

    VertexBuffer vbo;
    std::vector<float> vertices = {
        0, 1,   // TOP
        -1, -1, // BOTTOM LEFT
        1, -1   // BOTTOM RIGHT
    };
    unsigned int size = vertices.size() * sizeof(float);
    vbo.init(&vertices[0], size);

    VertexArray vao;
    vao.init();
    vao.setAttribute(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    Shader shader;
    shader.init("./src/Triangle.shader");
    shader.bind();

    // Main Loop
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
