//
// Created by 陈奕锟 on 2022/10/3.
//

#ifndef OPENGL_BASICRENDERERPROJECT_GLERRORDISPOSITION_H
#define OPENGL_BASICRENDERERPROJECT_GLERRORDISPOSITION_H

#endif //OPENGL_BASICRENDERERPROJECT_GLERRORDISPOSITION_H

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CompilerExtension.h"

#define ANY GLFW_OPENGL_ANY_PROFILE
#define COMPAT GLFW_OPENGL_COMPAT_PROFILE
#define CORE GLFW_OPENGL_CORE_PROFILE

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

void GLHint(int profile, int version_major, int version_minor);