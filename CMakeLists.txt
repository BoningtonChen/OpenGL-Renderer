cmake_minimum_required(VERSION 3.23)
project(OpenGL_BasicRendererProject)  # *记得变更项目名

set(CMAKE_CXX_STANDARD 23)  # *选择C++版本

# *添加额外头文件（记得更改项目名）
set(INC_DIR
        ${OpenGL_BasicRendererProject}dependencies/GLFW/include
        ${OpenGL_BasicRendererProject}dependencies/GLEW/include
        )
# *添加额外库（记得更改项目名）
set(LINK_DIR
        ${OpenGL_BasicRendererProject}dependencies/GLFW/lib
        ${OpenGL_BasicRendererProject}dependencies/GLEW/lib
        )

# *设置库目录
include_directories(
        ${INC_DIR}
)
link_directories(
        ${LINK_DIR}
)

# *定向可执行文件（记得变更项目名）
add_executable(
        OpenGL_BasicRendererProject src/Application.cpp
        src/CompilerExtension.h)

# *读取库地址（记得变更项目名）
target_link_libraries(
        OpenGL_BasicRendererProject
        # GLFW lib
        libglfw.3.dylib
        libglfw3.a
        # GLEW lib
        libGLEW.2.1.0.dylib
        libGLEW.2.1.dylib
        libGLEW.a

        pthread
        )

# *链接到OpenGL库（针对macOS）（记得变更项目名）
if (APPLE)
    target_link_libraries(OpenGL_BasicRendererProject "-framework OpenGL")
    target_link_libraries(OpenGL_BasicRendererProject "-framework GLUT")
endif()