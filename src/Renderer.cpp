//
// Created by 陈奕锟 on 2022/10/3.
//

#include "Renderer.h"

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetClearColor(Color color) const
{
    switch(color)
    {
        case Color::BLACK: // BLACK
            GLCall( glClearColor(0.0f, 0.0f, 0.0f, 1.0f) );
    }
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall( glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr) );
}