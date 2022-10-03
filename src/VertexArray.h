//
// Created by 陈奕锟 on 2022/10/3.
//

#ifndef OPENGL_BASICRENDERERPROJECT_VERTEXARRAY_H
#define OPENGL_BASICRENDERERPROJECT_VERTEXARRAY_H

#endif //OPENGL_BASICRENDERERPROJECT_VERTEXARRAY_H

#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};
