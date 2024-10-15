# OpenGL CheatSheet

* [Initialising OpenGL](#initialising-opengl)
  * [Init GLFW with the wanted OpenGL version](#init-glfw-with-the-wanted-opengl-version)
  * [Create a window](#create-a-window)
  * [Load GLAD](#load-glad)
  * [Set the Viewport](#set-the-viewport)
  * [Set the framebuffer resize callback](#set-the-framebuffer-resize-callback)
* [Drawing](#drawing)
  * [Create a Vertex Buffer Object (VBO) AND bind it](#create-a-vertex-buffer-object-(vbo)-and-bind-it)
  * [Pass the vertices data to the VBO](#pass-the-vertices-data-to-the-vbo)
  * [Create a Vertex Attribute Object AND bind it](#create-a-vertex-attribute-object-and-bind-it)
  * [Specify the vertices format to the VAO](#specify-the-vertices-format-to-the-vao)
  * [Create an Index Buffer Object (IBO) AND bind it](#create-an-index-buffer-object-(ibo)-and-bind-it)
  * [Pass the indices to the IBO](#pass-the-indices-to-the-ibo)
* [Terminology](#terminology)
* [Common Error](#common-error)


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


## Drawing

### Create a Vertex Buffer Object (VBO) AND bind it

```cpp
int vboId;
glGenBuffers(1, &vboId);
glBindBuffer(GL_ARRAY_BUFFER, vboId);
```

### Pass the vertices data to the VBO

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

### Create a Vertex Attribute Object AND bind it

```cpp
int vaoId;
glGenVertexArrays(1, &vaoId);
glBindVertexArray(vaoId);
```

### Specify the vertices format to the VAO

```cpp
glVertexAttribPointer(0,                 // index
                      3,                 // number of element of the attribute
                      GL_FLOAT,          // type
                      GL_FALSE,          // normalize ?
                      sizeof(float) * 3, // size of one vertex
                      (void*)0           // start of the attribute in the vertex
                      );
```

### Create an Index Buffer Object (IBO) AND bind it

```cpp
int iboId;
glGenBuffers(1, $iboId);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
```

### Pass the indices to the IBO

```cpp
//Be sure to have called glBindBuffer with the right buffer id before
//calling glBufferData
std::vector<unsigned int> ids = {0, 1, 2, 0, 1, 3};
glBufferData(GL_ELEMENT_ARRAY_BUFFER, ids.size() * sizeof(unsigned int), ids, GL_STATIC_DRAW);
```

## Terminology

* *GLFW*: GLFW is a library to manage windows and input. We could do without it but it would be cumbersome
* *GLAD*: OpenGL is only a specification, the implementation is provided by the GPU manufacturer inside the driver.
        GLAD allows to link the OpenGL function to their implementation inside the GPU driver.

## Common Error
