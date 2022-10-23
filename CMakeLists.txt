#设置cmake最小版本号
cmake_minimum_required(VERSION 3.17)

#设置项目名称
project(untitled)

#设置cpp使用标准
set(CMAKE_CXX_STANDARD 17)

#包含OpenGL接口依赖
include(CMakeLists.txt.glfw)

#源代码文件
add_executable(untitled engine/source/main.cpp ${glfw_sources})