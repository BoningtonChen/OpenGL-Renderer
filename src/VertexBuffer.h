//
// Created by 陈奕锟 on 2022/10/3.
//

#ifndef OPENGL_BASICRENDERERPROJECT_VERTEXBUFFER_H
#define OPENGL_BASICRENDERERPROJECT_VERTEXBUFFER_H

#endif //OPENGL_BASICRENDERERPROJECT_VERTEXBUFFER_H

#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererID;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};
