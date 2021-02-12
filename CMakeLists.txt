cmake_minimum_required(VERSION 3.10)
project(taiwancraft)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(deps/glfw/include)
include_directories(deps/glad/include)

add_subdirectory(deps/glfw)

add_executable(taiwancraft deps/glad/src/glad.c src/main.cpp)

target_link_libraries(taiwancraft glfw)