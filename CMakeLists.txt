cmake_minimum_required(VERSION 3.24)

project(polyhedron)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(polyhedron src/main.cpp)

# Assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# whereami
add_subdirectory(ext/whereami)

# GLAD
add_subdirectory(ext/glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(ext/glfw)

# GLM
add_subdirectory(ext/glm)

# TinyGLTF
set(TINYGLTF_HEADER_ONLY ON CACHE INTERNAL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)

# Library
add_library(lib STATIC
    include/polyhedron/core/renderer.h  lib/core/renderer.cpp
    include/polyhedron/core/transform.h lib/core/transform.cpp
    include/polyhedron/core/camera.h    lib/core/camera.cpp
    include/polyhedron/core/geometry.h  lib/core/geometry.cpp
    include/polyhedron/core/material.h  lib/core/material.cpp
    include/polyhedron/core/mesh.h      lib/core/mesh.cpp

    include/polyhedron/geometries/plane.h lib/geometries/plane.cpp
    include/polyhedron/geometries/cube.h  lib/geometries/cube.cpp

    include/polyhedron/materials/normal_material.h lib/materials/normal_material.cpp
    include/polyhedron/materials/pbr_material.h lib/materials/pbr_material.cpp

    include/polyhedron/loaders/gltf_loader.h lib/loaders/gltf_loader.cpp

    include/polyhedron/utils/file_utils.h lib/utils/file_utils.cpp
)
target_link_libraries(lib PUBLIC
    whereami
    glad
    glfw
    glm::glm
)
target_include_directories(lib PUBLIC
    include
    ext/stb
    ext/json
    ext/tinygltf
)

# Application
target_link_libraries(polyhedron PUBLIC lib)
target_include_directories(polyhedron PUBLIC include)
