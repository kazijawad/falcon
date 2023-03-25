cmake_minimum_required(VERSION 3.24)

project(falcon)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(falcon src/main.cpp)

# Assets
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/cmake/CopyAssets.cmake
)
add_dependencies(falcon assets)

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
    include/falcon/falcon.h

    include/falcon/core/camera.h                 lib/core/camera.cpp
    include/falcon/core/geometry.h               lib/core/geometry.cpp
    include/falcon/core/light.h                  lib/core/light.cpp
    include/falcon/core/material.h               lib/core/material.cpp
    include/falcon/core/mesh.h                   lib/core/mesh.cpp
    include/falcon/core/renderer.h               lib/core/renderer.cpp
    include/falcon/core/texture.h                lib/core/texture.cpp
    include/falcon/core/transform.h              lib/core/transform.cpp

    include/falcon/cameras/perspective_camera.h  lib/cameras/perspective_camera.cpp
    include/falcon/cameras/orthographic_camera.h lib/cameras/orthographic_camera.cpp

    include/falcon/controls/orbit_controls.h     lib/controls/orbit_controls.cpp

    include/falcon/geometries/plane.h            lib/geometries/plane.cpp
    include/falcon/geometries/cube.h             lib/geometries/cube.cpp

    include/falcon/materials/normal_material.h   lib/materials/normal_material.cpp
    include/falcon/materials/pbr_material.h      lib/materials/pbr_material.cpp

    include/falcon/textures/image_texture.h      lib/textures/image_texture.cpp

    include/falcon/lights/directional_light.h    lib/lights/directional_light.cpp
    include/falcon/lights/point_light.h          lib/lights/point_light.cpp

    include/falcon/loaders/gltf_loader.h         lib/loaders/gltf_loader.cpp

    include/falcon/utils/file_utils.h            lib/utils/file_utils.cpp
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
target_link_libraries(falcon PUBLIC lib)
target_include_directories(falcon PUBLIC include)
