# Polyhedron

An OpenGL real-time renderer.

## Features

- Scene Graph
- Standard Geometry
    - Plane
    - Cube
- Material System
    - Normal Material
    - Shader Material
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

2. Run the build shell script. If you're on Windows, you can replace `default-mac` inside the script with `default-windows`.
If you're using an IDE wth CMake support, you can choose the approriate configuration preset.

```bash
./build.sh
```

3. Run the built program.

```bash
./build/polyhedron
```
