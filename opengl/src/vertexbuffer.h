#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#pragma once

typedef struct VertexBuffer {
    int rendererId;
} VertexBuffer;

#endif

void InitVertexBuffer(VertexBuffer* vertexBuffer, const void* data, unsigned int size);
void BindVertexBuffer(VertexBuffer* vertexBuffer);
void UnbindVertexBuffer(VertexBuffer* vertexBuffer);