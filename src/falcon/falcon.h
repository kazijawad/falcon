#ifndef falcon_h
#define falcon_h

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace falcon {

class Camera;
class Geometry;
class ImageTexture;
class Light;
class Material;
class Mesh;
class OrbitControls;
class Texture;
class Transform;
class Renderer;
class RenderWindow;

struct RenderState;

static constexpr float PI = 3.14159265358979323846;

}

#endif
