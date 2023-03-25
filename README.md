# Falcon

A physically-based OpenGL real-time renderer built in C++. This is a personal project to experiment with various real-time rendering techniques.

Note: This project uses OpenGL 4.6 and will not work on macOS. In the future, I would like to support multiple backends with Metal support.

## Features

#### Scene Graph

Supports a dynamic scene graph and relative transformations with lazy evaluation for rendering optimization.

#### Material System

An extensible material system with support for physically based shading and custom GLSL shaders.

#### Mesh Processing

Supports standard geometry and glTF assets as indexed geometry.

## Installation

Falcon uses git submodules for external libraries. Therefore, it's important to  include the `--recursive` flag when cloning the repository:

```bash
git clone --recursive https://github.com/kazijawad/falcon.git
```

The project uses CMake for its build system and should work on any system that supports C++ 11 and OpenGL 4.6. An example build process could look like:

```bash
cmake -G "Ninja" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -S . -B build
cmake --build build -j 4
```

This would output the executable to `build/falcon`.
