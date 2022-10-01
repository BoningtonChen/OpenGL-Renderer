# OpenGL Simple Renderer Project
© Bonington Chen, 2022

## Description
- A Basic Modern OpenGL Renderer Project.
- Using C++ 23, OpenGL Version 4.1, as well as GLSL Version 330 core.
- Cross-platform, Support both Windows, macOS and Linux.

## Project Structure
- dependencies
  - GLAD
  - GLEW
  - GLFW
- res
  - shaders
    - Basic.shader
- src
  - Application.cpp
  - CompilerExtension.h
- .gitignore
- README.md
- CMakeLists.txt

### Comments
- Application.cpp file: \
Main Entrance of the Console Application.
- CompilerExtension.h: \
Cross-Platform Compiler Extensions, include a simulated MSVC __debugbreak() compiler function and so.