# EasyEngine project build entry.

cmake_minimum_required (VERSION 3.8)

include_directories(include)

link_directories(lib)

aux_source_directory(./source source_list)
aux_source_directory(./source/tool source_list)

message(STATUS "[Shine] source_list: ${source_list}")

add_executable (OpenGLTest ${source_list})

target_link_libraries(OpenGLTest glfw3  opengl32)