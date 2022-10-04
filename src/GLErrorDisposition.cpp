//
// Created by 陈奕锟 on 2022/10/3.
//

#include "GLErrorDisposition.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while ( GLenum error = glGetError() )
    {
        std::cout << "[OpenGL ERROR]" << "(" << error << "): " << "ISSUE Occurred in Function/Method: " << function << ", From: " << file << ", Line: " << line << std::endl;
        return false;
    }
    return true;
}

void GLHint(int hint, int version_major, int version_minor)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, hint);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
