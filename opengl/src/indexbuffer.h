#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#pragma once

typedef struct IndexBuffer {
    unsigned int rendererId;
} IndexBuffer;

#endif

void indexBufferInit(IndexBuffer* indexBuffer, const unsigned int* data, unsigned int count);
void indexBufferBind(IndexBuffer* indexBuffer);
void indexBufferUnbind(IndexBuffer* indexBuffer);