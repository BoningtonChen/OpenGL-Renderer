// * OpenGL header files
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// * C++ Standard Library header files
# include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// * Project Header files
#include "CompilerExtension.h"

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while ( GLenum error = glGetError() )
    {
        std::cout << "[OpenGL ERROR]" << "(" << error << "): " << "ISSUE Occurred in Function/Method: " << function << ", From: " << file << ", Line: " << line << std::endl;
        return false;
    }
    return true;
}

// ! 宏状态定义切换
#define SHADER_PARSE_STATUS_CHECK 1

struct ShaderProgramSource
{
public:
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while ( getline(stream, line) )
    {
        if ( line.find("#SHADER") != std::string::npos )
        {
            if ( line.find("Vertex") != std::string::npos )
                type = ShaderType::VERTEX;
            else if ( line.find("Fragment") != std::string::npos )
                type = ShaderType::FRAGMENT;
            else
            {
                ss[ (int)type ] << line << '\n';
            }
        }
    }

    return {
        ss[ (int)ShaderType::VERTEX ].str(),
        ss[ (int)ShaderType::FRAGMENT ].str()
    };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall( unsigned int id = glCreateShader(type) );
    const char* src = source.c_str();
    GLCall( glShaderSource(id, 1, &src, nullptr) );
    GLCall( glCompileShader(id) );

    int result;
    GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
    if (result == GL_FALSE)
    {
        int length;
        GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
        char* message = (char*)alloca( length * sizeof(char) );
        GLCall( glGetShaderInfoLog(id, length, &length, message) );

        std::cout << "[Shader Compile ERROR Messages]:" << std::endl;
        std::cout << "Fail to compile: " << (type == GL_VERTEX_SHADER ? "VERTEX " : "FRAGMENT ") << "Shader !" << std::endl;
        std::cout << message << std::endl;

        GLCall( glDeleteShader(id) );
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall( unsigned int program = glCreateProgram() );
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall( glAttachShader(program, vs) );
    GLCall( glAttachShader(program, fs) );

    GLCall( glLinkProgram(program) );
    GLCall( glValidateProgram(program) );

    GLCall( glDeleteShader(vs) );
    GLCall( glDeleteShader(fs) );

    return program;
}

int main(int argc, char* argv[], char **env)
{

    GLFWwindow* window;

    // ! 初始化项目库
    if ( !glfwInit() )
        return -1;

    // * Force set OpenGL Version to 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // ! 创建有效的 OpenGL Window 上下文
    window = glfwCreateWindow(640, 480, "Bonington's OpenGL Renderer Project", nullptr, nullptr);
    if ( !window )
    {
        glfwTerminate();
        return -1;
    }

    // ! 启用当前的 Window
    glfwMakeContextCurrent(window);

    // * 初始化 GLEW
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR!" << std::endl;

    // ! 输出 OpenGL(GLSL) 版本
    std::cout<< "OpenGL & Graphics Card Driver Version: " << glGetString(GL_VERSION) << std::endl;

    // ! OpenGL 准备工作
    float positions[] = {
            -0.5f, -0.5f,
            +0.5f, -0.5f,
            +0.5f, +0.5f,
            -0.5f, +0.5f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof positions, positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    unsigned int ibo;   // index buffer object
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof ibo, indices, GL_STATIC_DRAW);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall( glUseProgram(shader) );

#if SHADER_PARSE_STATUS_CHECK
    std::cout << "[VERTEX Shader]:" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "[FRAGMENT Shader]:" << std::endl;
    std::cout << source.FragmentSource << std::endl;
#endif

    // ! 循环当前窗口
    while ( !glfwWindowShouldClose(window) )
    {
        // ! 在此处渲染内容
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr) );

        // ! 交换前后端 buffer
        glfwSwapBuffers(window);

        // ! 推出项目
        glfwPollEvents();
    }

    GLCall( glDeleteProgram(shader); );

    glfwTerminate();


    // ! 控制台 console 获取主程序参数
    std::cout << std::endl;
    std::cout << "[Main function Parameters]: " <<std::endl;
    std::cout << "ARGc: " << argc << std::endl;
    std::cout << "ARGv Application root: " << argv[0] << std::endl;
    std::cout << "ARGv Pointer to an Array of main-func Parameters: " << argv << std::endl;
    std::cout << "ENVVAR value: " << env << std::endl;

    return 0;
}
