cmake_minimum_required(VERSION 3.24)

project(falcon)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# External Dependencies
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(TINYGLTF_HEADER_ONLY ON CACHE INTERNAL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)

add_subdirectory(src/ext/whereami)
add_subdirectory(src/ext/glad)
add_subdirectory(src/ext/glfw)
add_subdirectory(src/ext/glm)

# Library
set(FALCON_SOURCE_HEADERS
    src/falcon/falcon.h

    src/falcon/core/camera.h
    src/falcon/core/geometry.h
    src/falcon/core/light.h
    src/falcon/core/material.h
    src/falcon/core/mesh.h
    src/falcon/core/renderer.h
    src/falcon/core/texture.h
    src/falcon/core/transform.h

    src/falcon/cameras/perspective_camera.h
    src/falcon/cameras/orthographic_camera.h

    src/falcon/controls/orbit_controls.h

    src/falcon/geometries/plane.h
    src/falcon/geometries/cube.h

    src/falcon/materials/normal_material.h
    src/falcon/materials/pbr_material.h

    src/falcon/textures/image_texture.h

    src/falcon/lights/directional_light.h
    src/falcon/lights/point_light.h

    src/falcon/loaders/gltf_loader.h

    src/falcon/utils/file_utils.h

    src/falcon/render/window.h
)

set(FALCON_SOURCE
    src/falcon/core/camera.cpp
    src/falcon/core/geometry.cpp
    src/falcon/core/light.cpp
    src/falcon/core/material.cpp
    src/falcon/core/mesh.cpp
    src/falcon/core/renderer.cpp
    src/falcon/core/texture.cpp
    src/falcon/core/transform.cpp

    src/falcon/cameras/perspective_camera.cpp
    src/falcon/cameras/orthographic_camera.cpp

    src/falcon/controls/orbit_controls.cpp

    src/falcon/geometries/plane.cpp
    src/falcon/geometries/cube.cpp

    src/falcon/materials/normal_material.cpp
    src/falcon/materials/pbr_material.cpp

    src/falcon/textures/image_texture.cpp

    src/falcon/lights/directional_light.cpp
    src/falcon/lights/point_light.cpp

    src/falcon/loaders/gltf_loader.cpp

    src/falcon/utils/file_utils.cpp

    src/falcon/render/window.cpp
)

set(FALCON_INCLUDE src src/ext)

add_library(lib STATIC ${FALCON_SOURCE_HEADERS} ${FALCON_SOURCE})

target_link_libraries(lib PUBLIC
    whereami
    glad
    glfw
    glm::glm
)
target_include_directories(lib PUBLIC ${FALCON_INCLUDE})

# Main Application
add_executable(falcon src/falcon/cmd/falcon.cpp)

add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyAssets.cmake
)
add_dependencies(falcon assets)

target_link_libraries(falcon PUBLIC lib)
target_include_directories(falcon PUBLIC ${FALCON_INCLUDE})
