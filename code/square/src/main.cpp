#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// Init OpenGL
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

// Process Input
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// Shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position.xy, 1.0, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

unsigned int getShader(const char* shaderSource, GLenum shaderType) {
    unsigned int shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader compilation failed\n" << infoLog << std::endl;
    }
    return shader;
}


int main() {
    GLFWwindow *window = initOpenGL(600, 600, 3, 3);

    unsigned int vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    /*
     * 0----2
     * |    |
     * |    |
     * 1----3
     */
    std::vector<float> vertices = {
        -0.75, 0.75,  // 0
        -0.75, -0.75, // 1
        0.75, 0.75,   // 2
        0.75, -0.75   // 3
    };
    unsigned int size = vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], GL_STATIC_DRAW);

    unsigned int vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0);

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 1, 3
    };
    unsigned int iboId;
    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    unsigned int vertexShader = getShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = getShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Main Loop
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
