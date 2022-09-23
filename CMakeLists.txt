cmake_minimum_required(VERSION 3.24)

project(polyhedra)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(demo demo/main.cpp)

# stb
target_include_directories(demo PUBLIC external/stb)

# GLAD
add_subdirectory(external/glad)
target_link_libraries(demo PUBLIC glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
target_link_libraries(demo PUBLIC glfw)

# GLM
add_subdirectory(external/glm)
target_link_libraries(demo PUBLIC glm::glm)

# assimp
add_subdirectory(external/assimp)
target_link_libraries(demo PUBLIC assimp::assimp)

# Engine
add_library(engine STATIC
    include/camera.h src/camera.cpp
    include/program.h src/program.cpp
    include/mesh.h src/mesh.cpp
    include/model.h src/model.cpp
)
target_link_libraries(engine PUBLIC glad)
target_link_libraries(engine PUBLIC glfw)
target_link_libraries(engine PUBLIC glm::glm)
target_link_libraries(engine PUBLIC assimp::assimp)
target_include_directories(engine PUBLIC include)
target_include_directories(engine PUBLIC external/stb)

target_link_libraries(demo PUBLIC engine)
target_include_directories(demo PUBLIC include)
