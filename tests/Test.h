//
// Created by 陈奕锟 on 2022/10/5.
//

#ifndef OPENGL_BASICRENDERERPROJECT_TEST_H
#define OPENGL_BASICRENDERERPROJECT_TEST_H

#endif //OPENGL_BASICRENDERERPROJECT_TEST_H

#pragma once

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };
}