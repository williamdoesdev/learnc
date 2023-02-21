#include "indexbuffer.h"
#include "glerror.h"
#include <GLFW/glfw3.h>

void InitIndexBuffer(IndexBuffer* indexBuffer, const void* data, unsigned int size){
    GLWithError(glGenBuffers(1, &indexBuffer->rendererId));
    GLWithError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->rendererId));
    GLWithError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
};

void BindIndexBuffer(IndexBuffer* indexBuffer){
    GLWithError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->rendererId));
};

void UnbindIndexBuffer(IndexBuffer* indexBuffer){
    GLWithError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};