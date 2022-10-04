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

// * Project Header files
#include "CompilerExtension.h"
#include "GLErrorDisposition.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// ! 宏状态定义切换
#define MAIN_ARGS_RETRIEVE 1


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
            "Bonington's OpenGL Renderer Project",
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
    std::cout<< "OpenGL & Graphics Card Driver Version: " << glGetString(GL_VERSION) << std::endl;

    // ! 创建一个主函数内作用域，用于离开时在栈上销毁分配数据，阻止glfwTerminate()函数销毁OpenGL上下文时循环返回一个glError
    {
        // ! OpenGL 准备工作
        float positions[] = {
                100.0f, 100.0f, 0.0f, 0.0f,   // 0
                200.0f, 100.0f, 1.0f, 0.0f,   // 1
                200.0f, 200.0f, 1.0f, 1.0f,   // 2
                100.0f, 200.0f, 0.0f, 1.0f    // 3
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        GLCall( glEnable(GL_BLEND) );
        GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

        VertexArray va;
        VertexBuffer vb(positions, sizeof positions);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 projection = glm::ortho(
                0.0f, 960.0f,
                0.0f, 540.0f,
                -1.0f, 1.0f
                );

        glm::vec4 vp(100.0f, 100.0f, 0.0f, 1.0f);
        glm::vec4 result = projection * vp;

        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", projection);

        Texture texture("../res/textures/BonityLogo_light.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        // ! 循环当前窗口
        while (!glfwWindowShouldClose(window)) {

            // ! 在此处渲染内容
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", 0.2f, r, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(50ms);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            // ! 交换前后端 buffer
            glfwSwapBuffers(window);

            // ! 推出项目
            glfwPollEvents();
        }
    }

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
