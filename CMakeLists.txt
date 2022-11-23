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

# assimp
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
add_subdirectory(external/assimp)

# Library
add_library(lib STATIC
    include/poly/renderer.h lib/renderer.cpp
    include/poly/camera.h lib/camera.cpp
    include/poly/program.h lib/program.cpp
    include/poly/mesh.h lib/mesh.cpp
    include/poly/model.h lib/model.cpp
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
target_link_libraries(poly PUBLIC lib)
target_include_directories(poly PUBLIC
    include
    external/stb
)
