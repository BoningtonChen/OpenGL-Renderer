//
// Created by 陈奕锟 on 2022/10/5.
//

#include "Test.h"



namespace test
{
    TestMenu::TestMenu(Test*& currentTestPointer)
        : m_CurrentTest(currentTestPointer)
    {

    }

    void TestMenu::OnImGuiRender()
    {
        for (auto& test : m_Tests)
        {
            if ( ImGui::Button(test.first.c_str()) )
                m_CurrentTest = test.second();
        }
    }
}
