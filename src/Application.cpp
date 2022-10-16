// * OpenGL header files
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// * OpenGL explicit define
#define GLEW_STATIC

// * C++ Standard Library header files
# include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <future>

// * OpenGL Vendor header files
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// * Project src Header files
#include "CompilerExtension.h"
#include "GLErrorDisposition.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// * Project tests Header files
#include "Test.h"
#include "TestClearColor.h"
#include "TestTexture2D.h"

// ! 宏状态定义切换
#define MAIN_ARGS_RETRIEVE 0

int main(int argc, char* argv[], char **env)
{

    GLFWwindow* window;

    // ! 初始化项目库
    if ( !glfwInit() )
        return -1;

    // * Force set OpenGL Version to 4.1 Core Profile
    GLHint(CORE, 4, 1);

    // ! 创建有效的 OpenGL Window 上下文
    window = glfwCreateWindow(
            960, 540,
            "Bonington's OpenGL Basic Renderer Project",
            nullptr, nullptr
            );
    if ( !window )
    {
        glfwTerminate();
        return -1;
    }

    // ! 启用当前的 Window
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // * 初始化 GLEW
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR!" << std::endl;

    // ! 输出 OpenGL(GLSL) 版本
    std::cout << "OpenGL & Graphics Card Driver Version: " << glGetString(GL_VERSION) << std::endl;

    // ! 创建一个主函数内作用域，用于离开时在栈上销毁分配数据，阻止glfwTerminate()函数销毁OpenGL上下文时循环返回一个glError
    {
        GLCall( glEnable(GL_BLEND) );
        GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();

        // * 需要指定glsl版本, 也就是shader中的version
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);

        test::Test* currentTest = nullptr;
        auto* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu -> RegisterTest<test::TestClearColor>("Clear Color");
        testMenu -> RegisterTest<test::TestTexture2D>("Texture 2D");

        // ! 循环当前窗口
        while (!glfwWindowShouldClose(window))
        {
            // ! 在此处渲染内容
            renderer.SetClearColor(Color::BLACK);
            renderer.Clear();

            // * 新建一个 ImGui 上下文，用于生成监视窗口
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest)
            {
                currentTest -> OnUpdate(0.0f);
                currentTest -> OnRender();
                ImGui::Begin("Test");

                if ( currentTest != testMenu && ImGui::Button("<-") )
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest -> OnImGuiRender();

                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

            // ! 交换前后端 buffer
            glfwSwapBuffers(window);

            // ! 推出项目
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }

    // ! 停止并销毁 ImGui 窗口
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    // ! 销毁 OpenGL 上下文
    glfwTerminate();


#if MAIN_ARGS_RETRIEVE
    // ! 控制台 console 获取主程序参数
    std::cout << std::endl;
    std::cout << "[Main function Parameters]: " <<std::endl;
    std::cout << "ARGc: " << argc << std::endl;
    std::cout << "ARGv [Application main root]: " << argv[0] << std::endl;
    std::cout << "ARGv pointer to [Main-func Parameters]: " << argv << std::endl;
    std::cout << "ENVVAR pointer: " << env << std::endl;
#endif

    return 0;
}
