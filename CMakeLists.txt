cmake_minimum_required(VERSION 3.23.2)
project(OpenGL_BasicRendererProject)  # *记得变更项目名

set(CMAKE_CXX_STANDARD 14)  # *选择C++版本
set(CMAKE_C_STANDARD 23)    # *选择C版本

# *添加额外头文件（记得更改项目名）
set(INC_DIR
        ${OpenGL_BasicRendererProject}dependencies/GLFW/include/
        ${OpenGL_BasicRendererProject}dependencies/GLEW/include/
        ${OpenGL_BasicRendererProject}dependencies/GLAD/include/

        ${OpenGL_BasicRendererProject}vendor/glm/
        ${OpenGL_BasicRendererProject}vendor/stb/
        ${OpenGL_BasicRendererProject}vendor/imgui/

        ${OpenGL_BasicRendererProject}src/
        ${OpenGL_BasicRendererProject}tests/
        )
# *添加额外库（记得更改项目名）
set(LINK_DIR
        ${OpenGL_BasicRendererProject}dependencies/GLFW/lib/
        ${OpenGL_BasicRendererProject}dependencies/GLEW/lib/
        )

# *设置库目录
include_directories(
        ${INC_DIR}
)
link_directories(
        ${LINK_DIR}
)

# *定向可执行文件（记得变更项目名）
add_executable(OpenGL_BasicRendererProject
        # *Vendor dependencies
        vendor/stb/stb_image/stb_image.h
        vendor/stb/stb_image/stb_image.cpp

        vendor/imgui/imgui/imconfig.h

        vendor/imgui/imgui/imgui.cpp
        vendor/imgui/imgui/imgui.h

        vendor/imgui/imgui/imgui_demo.cpp

        vendor/imgui/imgui/imgui_draw.cpp

        vendor/imgui/imgui/imgui_impl_glfw.h
        vendor/imgui/imgui/imgui_impl_glfw.cpp

        vendor/imgui/imgui/imgui_impl_glut.h
        vendor/imgui/imgui/imgui_impl_glut.cpp

        vendor/imgui/imgui/imgui_impl_opengl3.h
        vendor/imgui/imgui/imgui_impl_opengl3.cpp
        vendor/imgui/imgui/imgui_impl_opengl3_loader.h

        vendor/imgui/imgui/imgui_internal.h

        vendor/imgui/imgui/imgui_tables.cpp

        vendor/imgui/imgui/imgui_widgets.cpp

        vendor/imgui/imgui/imstb_rectpack.h
        vendor/imgui/imgui/imstb_textedit.h
        vendor/imgui/imgui/imstb_truetype.h
        vendor/imgui/imgui/imstb_truetype.h
        # *GLAD dependencies

        # *GLEW dependencies

        # *GLFW dependencies

        # *Project files
        src/Application.cpp

        src/CompilerExtension.h

        src/Renderer.cpp
        src/Renderer.h

        src/VertexBuffer.cpp
        src/VertexBuffer.h

        src/IndexBuffer.cpp
        src/IndexBuffer.h

        src/VertexArray.cpp
        src/VertexArray.h

        src/VertexBufferLayout.cpp
        src/VertexBufferLayout.h

        src/Shader.cpp
        src/Shader.h

        src/GLErrorDisposition.cpp
        src/GLErrorDisposition.h

        src/Texture.cpp
        src/Texture.h

        tests/Test.h
        tests/TestClearColor.cpp
        tests/TestClearColor.h
        tests/Test.cpp
        tests/TestTexture2D.cpp
        tests/TestTexture2D.h
        )

# *读取库地址（记得变更项目名）
target_link_libraries(
        OpenGL_BasicRendererProject
        # *GLFW lib
        libglfw.3.dylib
        libglfw3.a

        # *GLEW lib
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
