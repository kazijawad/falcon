# Polyhedron

An OpenGL real-time renderer.

Note: This project is set to OpenGL 4.6 and will not work on macOS because macOS only supports up to OpenGL 4.1.

## Features

- Scene Graph
- Standard Geometry
    - Plane
    - Cube
- Material System
    - Normal Material
    - PBR Material
- Physically Based Shading
- GLTF Loader

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

Please make sure you have at minimum [CMake](https://cmake.org) 3.25 and Clang.

### Installation

1. Clone the repository. It's important to include the `--recursive` flag to include the external dependencies that are linked with git submodules.

```bash
git clone --recursive https://github.com/kazijawad/polyhedron.git
```

2. Build the project using CMake. If you're using an IDE wth CMake support, you can choose the approriate configuration preset.

```bash
cmake --preset default
cmake --build --preset default
```

3. Run the built program.

```bash
./build/polyhedron
```
