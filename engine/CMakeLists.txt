# CMakeList.txt: EasyEngine 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories(include)

link_directories(lib)

aux_source_directory(./source source_list)

add_executable (OpenGLTest ${source_list})

target_link_libraries(OpenGLTest glfw3  opengl32)