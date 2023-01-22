#ifndef polyhedron_h
#define polyhedron_h

#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace polyhedron {

class Transform;
class Geometry;
class Material;
class Mesh;
class Camera;

}

#endif