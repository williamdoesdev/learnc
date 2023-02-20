#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "fileio.h"

#define GLWithError(x) GLClearError();\
    x;\
    GLCheckError(#x, __FILE__, __LINE__);

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError(const char* currentFunction, const char* currentFile, int currentLine)
{
    bool isError = true;
    bool wasError = false;
    do {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            printf("OpenGL error: %d\n", error);
            printf("Function: %s\n", currentFunction);
            printf("File: %s\n", currentFile);
            printf("Line: %d\n", currentLine);
            wasError = true;
        } else {
            isError = false;
        }
    } while (isError == true);
    assert(wasError == false);
};

// Compile either a vertex or fragment shader from source
static unsigned int CompileShader(const char* source, unsigned int type)
{
    // Get an id for the shader
    unsigned int id = glCreateShader(type);
    //Create shader
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        // Get length of error message
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // Allocate memory for error message
        char* message = (char*)alloca(length * sizeof(char));
        // Get error message
        glGetShaderInfoLog(id, length, &length, message);
        // Print error message
        printf("Failed to compile %s shader!\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        // Delete shader since it failed to compile
        glDeleteShader(id);

        return 0;
    };

    return id;
}

// Create a shader program from vertex and fragment shader source
static unsigned int CreateShaderProgram(const char* vertexShader, const char* fragmentShader)
{
    // Create a program
    unsigned int program = glCreateProgram();
    // Compile shaders
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    // Attach shaders to program
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // Link program
    glLinkProgram(program);

    // Validate program
    glValidateProgram(program);

    // Delete shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        printf("Error!");

    // Create vao
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Triangle vertex positions    
    float positions[] = {
        -0.5f, -0.5f,
         0.5f,  -0.5f,
         0.5f, 0.5f,
         -0.5f, 0.5f
    };
    
    // Create vertex buffer
    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Copy vertex positions to buffer
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    // Create index array
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Create index buffer
    unsigned int indexBuffer;
    glGenBuffers(1, &indexBuffer);

    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    // Copy index positions to buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


    // Define attribute for vertex positions
    // Basically, this defines the 'schema' of the data that we passed to the buffer above
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    // You also have to enable the attribute
    glEnableVertexAttribArray(0);

    // Define shader source
    const char* vertexShader = getFileString("res/shaders/triangle.vert");
    const char* fragmentShader = getFileString("res/shaders/triangle.frag");

    // Create and bind shader program
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    free((void*)vertexShader);
    free((void*)fragmentShader);

    /* Loop until the user closes the window */

    //Change colors over time
    float r = 0.0f;
    float g = 1.0f;
    float b = 1.0f;
    float interval = 0.01f;
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw call
        GLWithError(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

        //Change colors over time
        if(r > 1.0f)
            interval = -0.05f;
        else if(r < 0.0f)
            interval = 0.05f;
        
        r += interval;

        glUniform4f(glGetUniformLocation(shaderProgram, "u_Color"), r, g, b, 1.0f);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}