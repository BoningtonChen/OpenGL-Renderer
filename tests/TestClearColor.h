//
// Created by 陈奕锟 on 2022/10/5.
//

#ifndef OPENGL_BASICRENDERERPROJECT_TESTCLEARCOLOR_H
#define OPENGL_BASICRENDERERPROJECT_TESTCLEARCOLOR_H

#endif //OPENGL_BASICRENDERERPROJECT_TESTCLEARCOLOR_H

#pragma once

#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_ClearColor[4];
    };
}
