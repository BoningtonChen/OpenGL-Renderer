//
// Created by 陈奕锟 on 2022/10/3.
//

#ifndef OPENGL_BASICRENDERERPROJECT_VERTEXBUFFERLAYOUT_H
#define OPENGL_BASICRENDERERPROJECT_VERTEXBUFFERLAYOUT_H

#endif //OPENGL_BASICRENDERERPROJECT_VERTEXBUFFERLAYOUT_H

#pragma once

#include <GL/glew.h>
#include <vector>

#include "GLErrorDisposition.h"

struct VertexBufferElement
{
public:
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                return 0;
        }
        ASSERT(false);
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout()
        :m_Stride(0)
    {}

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(true, "Templated function return an ERROR ! ");
    }

    template<>
    void Push<float>(unsigned int count)
    {
        m_Elements.push_back( {GL_FLOAT, count, GL_FALSE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};
