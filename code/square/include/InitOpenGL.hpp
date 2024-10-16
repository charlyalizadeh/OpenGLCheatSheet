#ifndef INITOPENGL_H
#define INITOPENGL_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

void initGLFW(int minor, int major);
GLFWwindow* createWindow(int width, int height);
void framebufferSizCallback(GLFWwindow* window, int width, int height);
GLFWwindow* initOpenGL(int width, int height, int minor, int major);

#endif
