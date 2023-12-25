cmake_minimum_required(VERSION 3.21)
 
project(my_project)
 
find_package(OpenGL REQUIRED)
add_library(glad glad/src/glad.c)
target_include_directories(glad  PUBLIC glad/include)
 
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl") 
 
add_executable(01_rectangle 01_rectangle.cpp)
add_executable(02_uniform_GLSL 02_uniform_GLSL.cpp)
add_executable(03_2_attributes 03_2_attributes.cpp)
add_executable(04_customized_shader 04_customized_shader.cpp)
add_executable(05_texture 05_texture.cpp)
add_executable(06_dual_texture 06_dual_texture.cpp)
add_executable(07_transformations 07_transformations.cpp)


target_link_libraries(01_rectangle glfw ${GL_LIBRARY} glad)
target_link_libraries(02_uniform_GLSL glfw ${GL_LIBRARY} glad)
target_link_libraries(03_2_attributes glfw ${GL_LIBRARY} glad)
target_link_libraries(04_customized_shader glfw ${GL_LIBRARY} glad)
target_link_libraries(05_texture glfw ${GL_LIBRARY} glad)
target_link_libraries(06_dual_texture glfw ${GL_LIBRARY} glad)
target_link_libraries(07_transformations glfw ${GL_LIBRARY} glad)