#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void initGLFW(int minor, int major) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, minor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, major);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(int width, int height) {
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    return window;
}

void framebufferSizCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initOpenGL(int width, int height, int minor, int major) {
    initGLFW(minor, minor);

    GLFWwindow* window = createWindow(width, height);
    if(window == nullptr) { return nullptr; }

    // Load GLAD1
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // We should destroy the previously allocated window if GLAD doesn't load
        glfwDestroyWindow(window);
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // Viewport
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebufferSizCallback);

    return window;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    GLFWwindow *window = initOpenGL(600, 600, 3, 3);

    // Main Loop
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
