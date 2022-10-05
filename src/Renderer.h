//
// Created by 陈奕锟 on 2022/10/3.
//

#ifndef OPENGL_BASICRENDERERPROJECT_RENDERER_H
#define OPENGL_BASICRENDERERPROJECT_RENDERER_H

#endif //OPENGL_BASICRENDERERPROJECT_RENDERER_H

#pragma once

#include <array>

#include <GL/glew.h>

#include "GLErrorDisposition.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


enum struct Color
{
    BLACK
};
class Renderer
{
public:
    void Clear() const;
    void SetClearColor(Color color) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
