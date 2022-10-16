//
// Created by 陈奕锟 on 2022/10/16.
//

#ifndef OPENGL_BASICRENDERERPROJECT_TESTTEXTURE2D_H
#define OPENGL_BASICRENDERERPROJECT_TESTTEXTURE2D_H

#endif //OPENGL_BASICRENDERERPROJECT_TESTTEXTURE2D_H

#pragma once

#include "Test.h"

#include <memory>

#include <GL/glew.h>

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLErrorDisposition.h"
#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Projection;
        glm::mat4 m_View;
        glm::vec3 m_TranslationA;
        glm::vec3 m_TranslationB;

    };
}