# OpenGL CheatSheet


* [Setup OpenGL](#setup-opengl)
* [Initialising OpenGL](#initialising-opengl)
  * [Init GLFW with the wanted OpenGL version](#init-glfw-with-the-wanted-opengl-version)
  * [Create a window](#create-a-window)
  * [Load GLAD](#load-glad)
  * [Set the Viewport](#set-the-viewport)
  * [Set the framebuffer resize callback](#set-the-framebuffer-resize-callback)
* [Vertex Buffer Object](#vertex-buffer-object)
* [Vertex Attribute Object](#vertex-attribute-object)
* [Index Buffer Object](#index-buffer-object)
* [Example](#example)
* [Terminology](#terminology)
* [Source](#source)

## Setup OpenGL

* [learnopengl tutorial (Windows / Linux)](https://learnopengl.com/Getting-started/Creating-a-window)
* [Cherno tutorial (Windows)](https://youtu.be/OR4fNpBjmq8?si=B-6Nb8yBKXTdGV1s)


## Initialising OpenGL

### Init GLFW with the wanted OpenGL version

```cpp
void initGLFW(int minor, int major) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, minor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, major);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
```

### Create a window

```cpp
GLFWwindow* createWindow(int width, int height) {
    GLFWwindow* window = glfwCreateWindow(width, height, "Window Name", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    return window;
}
```

### Load GLAD

```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return nullptr;
}
```

### Set the Viewport

```cpp
glViewport(0, 0, width, height);
```

### Set the framebuffer resize callback

```cpp
void framebufferSizCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

glfwSetFramebufferSizeCallback(window, framebufferSizCallback);
```



## Vertex Buffer Object

Create and bind the vertex buffer object (VBO)  
```cpp
unsigned int vboId;
glGenBuffers(1, &vboId);
glBindBuffer(GL_ARRAY_BUFFER, vboId);
```

Pass the data to the VBO (to the GPU)  
```cpp
//Be sure to have called glBindBuffer with the right buffer id before
//calling glBufferData
vector<float> vertices = {
    1., 0., 0.,
    0., 1., 0.,
    0., 0., 1.,
    0., 0., 1.
};
unsigned int size = vertices.size() * sizeof(float);
glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
```

## Vertex Attribute Object

Create and bind the Vertex Attribute Object (VAO)  
```cpp
unsigned int vaoId;
glGenVertexArrays(1, &vaoId);
glBindVertexArray(vaoId);
```

Specify the vertices format to the VAO
```cpp
glVertexAttribPointer(0,                 // index
                      3,                 // number of element of the attribute
                      GL_FLOAT,          // type
                      GL_FALSE,          // normalize ?
                      sizeof(float) * 3, // size of one vertex
                      (void*)0           // start of the attribute in the vertex
                      );
glEnableVertexAttribArray(0);
```

## Index Buffer Object

Create and bind the Index Buffer Object (IBO)  
```cpp
int iboId;
glGenBuffers(1, $iboId);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
```

Pass the indices to the IBO  
```cpp
//Be sure to have called glBindBuffer with the right buffer id before
//calling glBufferData
std::vector<unsigned int> ids = {0, 1, 2, 0, 1, 3};
glBufferData(GL_ELEMENT_ARRAY_BUFFER, ids.size() * sizeof(unsigned int), ids, GL_STATIC_DRAW);
```

## Examples

* [Create a window](./code/window/)
* [Draw a triangle](./code/triangle/)
* [Draw a triangle using Object Oriented paradigm](./code/triangle_OO/)
* [Draw a square reusing vertices multiple times (Index Buffer)](./code/square)

## Projects

* [Maze generation](https://github.com/charlyalizadeh/OpenGLMaze)

## Terminology

* *GLFW*: GLFW is a library to manage windows and input. We could do without it but it would be cumbersome
* *GLAD*: OpenGL is only a specification, the implementation is provided by the GPU manufacturer inside the driver.
        GLAD allows to link the OpenGL function to their implementation inside the GPU driver.

## Source

* [Jamie King youtube channel](https://www.youtube.com/@JamieKingCS) and more particulary his [3D Computer Graphics Using OpenGL playlist](https://youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY&si=4hb-MTGaW3H6sSE3)
* [Chermo Opengl playlist](https://youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&si=WxrcIndFibol52dQ)
* [learnopengl website](https://learnopengl.com/)
