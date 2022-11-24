cmake_minimum_required(VERSION 3.24)

project(poly)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(poly src/main.cpp)

# GLAD
add_subdirectory(external/glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLM
add_subdirectory(external/glm)

# TinyGLTF
set(TINYGLTF_HEADER_ONLY ON CACHE INTERNAL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)

# Library
add_library(lib STATIC
    include/poly/core/renderer.h  lib/core/renderer.cpp
    include/poly/core/transform.h lib/core/transform.cpp
    include/poly/core/camera.h    lib/core/camera.cpp
    include/poly/core/program.h   lib/core/program.cpp
    include/poly/core/geometry.h  lib/core/geometry.cpp
    include/poly/core/mesh.h      lib/core/mesh.cpp

    include/poly/geometries/plane.h      lib/geometries/plane.cpp

    include/poly/loaders/gltf_loader.h      lib/loaders/gltf_loader.cpp
)
target_link_libraries(lib PUBLIC
    glad
    glfw
    glm::glm
)
target_include_directories(lib PUBLIC
    include
    external/stb
    external/json
    external/tinygltf
)

# Application
target_link_libraries(poly PUBLIC lib)
target_include_directories(poly PUBLIC include)
