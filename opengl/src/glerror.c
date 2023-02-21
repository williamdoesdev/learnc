#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <GLFW/glfw3.h>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

void GLCheckError(const char* currentFunction, const char* currentFile, int currentLine)
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