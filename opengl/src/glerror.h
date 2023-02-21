#ifndef GLERROR_H
#define GLERROR_H
#pragma once

#define GLWithError(x) GLClearError();\
    x;\
    GLCheckError(#x, __FILE__, __LINE__);

#endif

void GLClearError();
void GLCheckError(const char* currentFunction, const char* currentFile, int currentLine);