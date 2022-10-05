//
// Created by 陈奕锟 on 2022/10/5.
//

#ifndef OPENGL_BASICRENDERERPROJECT_TEST_H
#define OPENGL_BASICRENDERERPROJECT_TEST_H

#endif //OPENGL_BASICRENDERERPROJECT_TEST_H

#pragma once

#include "iostream"
#include <vector>
#include <functional>

#include "imgui/imgui.h"

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

    class TestMenu : public Test
    {
    public:
        explicit TestMenu(Test*& currentTestPointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "[Registering test]: " << name << std::endl;
            m_Tests.emplace_back( std::make_pair(name, []() { return new T(); }) );
        }

    private:
        Test*& m_CurrentTest;
        std::vector< std::pair< std::string, std::function<Test*()> > > m_Tests;
    };
}