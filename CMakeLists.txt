cmake_minimum_required(VERSION 3.24)

project(polyhedra)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(render src/main.cpp)

# GLAD
add_subdirectory(external/glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLM
add_subdirectory(external/glm)

# assimp
add_subdirectory(external/assimp)

# Library
add_library(lib STATIC
    include/camera.h lib/camera.cpp
    include/program.h lib/program.cpp
    include/mesh.h lib/mesh.cpp
    include/model.h lib/model.cpp
)
target_link_libraries(lib PUBLIC
    glad
    glfw
    glm::glm
    assimp::assimp
)
target_include_directories(lib PUBLIC
    include
    external/stb
)

# Application
target_link_libraries(render PUBLIC lib)
target_include_directories(render PUBLIC
    include
    external/stb
)
