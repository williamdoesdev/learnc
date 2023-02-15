#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

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
        printf("Failed to compile %s shader!", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
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

    // Triangle vertex positions    
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    
    // Create vertex buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Copy vertex positions to buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // Define attribute for vertex positions
    // Basically, this defines the 'schema' of the data that we passed to the buffer above
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    // You also have to enable the attribute
    glEnableVertexAttribArray(0);

    // Define shader source
    const char* vertexShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}";

    const char* fragmentShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}";

    // Create and bind shader program
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw call
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}