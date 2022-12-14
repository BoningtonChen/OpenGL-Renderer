//
// Created by 陈奕锟 on 2022/10/3.
//

#include "Shader.h"

# include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "GLErrorDisposition.h"

Shader::Shader(const std::string &filepath)
    :m_Filepath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall( glDeleteProgram(m_RendererID) );
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{

    std::ifstream stream(filepath, std::ios::in);

    // ! 进行文件路径校验
    if ( !stream.is_open() )
    {
        std::cout << "Cannot find " << filepath << " ! :(" << std::endl;
    }

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
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
        }
        else
        {
            ss[ (int)type ] << line << '\n';
        }
    }

    return {
            ss[ (int)ShaderType::VERTEX ].str(),
            ss[ (int)ShaderType::FRAGMENT ].str()
    };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

void Shader::Bind() const
{
    GLCall( glUseProgram(m_RendererID) );
}

void Shader::Unbind() const
{
    GLCall( glUseProgram(0) );
}

void Shader::SetUniform1i(const std::string &name, int value)
{
    GLCall( glUniform1i(GetUniformLocation(name), value) );
}
void Shader::SetUniform1f(const std::string &name, float value)
{
    GLCall( glUniform1f(GetUniformLocation(name), value) );
}
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall( glUniform4f(GetUniformLocation(name), v0, v1, v2, v3) );
}
void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    GLCall( glUniformMatrix4fv( GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0] ) );
}

int Shader::GetUniformLocation(const std::string &name)
{
    if ( m_UniformLocationCache.find(name) != m_UniformLocationCache.end() )
        return m_UniformLocationCache[name];
    GLCall( int location = glGetUniformLocation(m_RendererID, name.c_str()) );
    if (location == -1)
        std::cout << "[WARNING]: Uniform " << name << " DOESN'T EXIST!" << ", func implemented in: Shader.cpp, [function signature]: int GLGetUniformLocation(const std::string& " << name << ")." << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}
