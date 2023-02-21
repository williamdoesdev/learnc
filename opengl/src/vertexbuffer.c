#include "vertexbuffer.h"
#include "glerror.h"
#include <GLFW/glfw3.h>

void InitVertexBuffer(VertexBuffer* vertexBuffer, const void* data, unsigned int size){
    GLWithError(glGenBuffers(1, &vertexBuffer->rendererId));
    GLWithError(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->rendererId));
    GLWithError(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
};

void BindVertexBuffer(VertexBuffer* vertexBuffer){
    GLWithError(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->rendererId));
};

void UnbindVertexBuffer(VertexBuffer* vertexBuffer){
    GLWithError(glBindBuffer(GL_ARRAY_BUFFER, 0));
};