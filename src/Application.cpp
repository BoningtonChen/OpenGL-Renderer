// * OpenGL header files
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// * C++ Standard Library header files
# include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// ! 在macOS上实现MSVC的 __debugbreak(); 编译器函数
#if defined(__APPLE__) && defined(__aarch64__)
#define __debugbreak() __asm__ __volatile__(
    "   mov    x0, %x0;
" /* pid                */
    "   mov    x1, #0x11;
" /* SIGSTOP            */
    "   mov    x16, #0x25;
" /* syscall 37 = kill  */
    "   svc    #0x80
" /* software interrupt */
    "   mov    x0, x0
" /* nop                */
    ::  "r"(getpid())
    :   "x0", "x1", "x16", "memory")
#elif defined(__APPLE__) && defined(__arm__)
#define __debugbreak() __asm__ __volatile__(
    "   mov    r0, %0;
" /* pid                */
    "   mov    r1, #0x11;
" /* SIGSTOP            */
    "   mov    r12, #0x25;
" /* syscall 37 = kill  */
    "   svc    #0x80
" /* software interrupt */
    "   mov    r0, r0
" /* nop                */
    ::  "r"(getpid())
    :   "r0", "r1", "r12", "memory")
#elif defined(__APPLE__) && ( defined(__i386__) || defined(__x86_64__) )
#define __debugbreak() __asm__ __volatile__("int $3; mov %eax, %eax")
#endif

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
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca( length * sizeof(char) );
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "[Shader Compile ERROR Messages]:" << std::endl;
        std::cout << "Fail to compile: " << (type == GL_VERTEX_SHADER ? "VERTEX " : "FRAGMENT ") << "Shader !" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

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
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

#if SHADER_PARSE_STATUS_CHECK
    std::cout << "[VERTEX Shader]:" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "[FRAGMENT Shader]:" << std::endl;
    std::cout << source.FragmentSource << std::endl;
#endif

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    // ! 循环当前窗口
    while ( !glfwWindowShouldClose(window) )
    {
        // ! 在此处渲染内容
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ! 交换前后端 buffer
        glfwSwapBuffers(window);

        // ! 推出项目
        glfwPollEvents();
    }

    glDeleteProgram(shader);

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
