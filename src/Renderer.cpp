//
// Created by 陈奕锟 on 2022/10/3.
//

#include "Renderer.h"

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