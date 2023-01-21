#ifndef renderer_h
#define renderer_h

#include <functional>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace polyhedron {

class Transform;
class Camera;

class Renderer {
public:
    unsigned int width;
    unsigned int height;

    std::shared_ptr<Transform> scene;
    std::shared_ptr<Camera> camera;

    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    void setClearColor(float r, float g, float b, float a);

    void clearColor();
    void clearDepth();
    void clearStencil();
    void clear(bool color = true, bool depth = true, bool stencil = true);

    void run(std::function<void()> fn);

    void render();

    void terminate();

private:
    GLFWwindow* window;

    bool resize();
};

}

#endif
