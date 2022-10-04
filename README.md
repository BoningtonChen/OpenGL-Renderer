# OpenGL Simple Renderer Project
© Bonington Chen, 2022

<!-- TOC -->
* [OpenGL Simple Renderer Project](#opengl-simple-renderer-project)
  * [Description](#description)
  * [Project Structure](#project-structure)
  * [Comments](#comments)
  * [Building Tools](#building-tools)
<!-- TOC -->

## Description
- A Basic Modern OpenGL Renderer Project.
- Using C++ 23, C 23, OpenGL Version 3.3 && 4.1, as well as GLSL Version 330 core.
- Cross-platform, Support both Windows, macOS and Linux.

## Project Structure
- dependencies
  - GLAD
  - GLEW
  - GLFW
- res
  - shaders
    - Basic.shader
- vendor
  - stb_image.h
  - stb_image.cpp
- src
  - Application.cpp
  - CompilerExtension.h
  - GLErrorDisposition.h
  - GLErrorDisposition.cpp
  - Renderer.h
  - Renderer.cpp
  - VertexBuffer.h
  - VertexBuffer.cpp
  - VertexBufferLayout.h
  - VertexBufferLayout.cpp
  - IndexBuffer.h
  - IndexBuffer.cpp
  - Shader.h
  - Shader.cpp
  - Texture.h
  - Texture.cpp
- .gitignore
- README.md
- CMakeLists.txt

## Comments
- Application.cpp : \
Main Entrance of the Console Application.
- CompilerExtension.h : \
Cross-Platform Compiler Extensions, include a simulated MSVC __debugbreak() compiler function and so.
- GLErrorDisposition.h / GLErrorDisposition.cpp : \
Definitions and Implementation methods of GLLogCall() functions and so.
- IndexBuffer.h / IndexBuffer.cpp : \
Definitions and Implementation methods of IndexBuffer.
- VertexBuffer.h / VertexBuffer.cpp : \
  Definitions and Implementation methods of VertexBuffer.
- VertexBufferLayout.h / VertexBufferLayout.cpp : \
  Definitions and Implementation methods of VertexBufferLayout.
- Shader.h / Shader.cpp : \
Definitions and Implementation methods of Shader-related types, including ShaderProgramSource and so.
- Renderer.h / Renderer.cpp : \
Definitions and Implementation method of Renderer type.
- Texture.h / Texture.cpp : \
  Definitions and Implementation method of Texture type.

## Building Tools
- Developing Tools
  - JetBrains CLion
  - SnippetsLab
  - Ninja
  - CMake
- Vendors
  - stb_image
- Version Control
  - GitLink
  - GitHub
- References
  - Dash