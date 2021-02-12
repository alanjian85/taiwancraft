cmake_minimum_required(VERSION 3.10)
project(taiwancraft)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(deps/glfw/include
					deps/glad/include
					deps/glm
					deps/stb)

add_subdirectory(deps/glfw)

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

file(GLOB_RECURSE SHADER_FILES
	${CMAKE_SOURCE_DIR}/assets/shaders/*.vert
	${CMAKE_SOURCE_DIR}/assets/shaders/*.frag
	${CMAKE_SOURCE_DIR}/assets/shaders/*.geom)

add_executable(${PROJECT_NAME} deps/glad/src/glad.c ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

target_link_libraries(${PROJECT_NAME} glfw)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})