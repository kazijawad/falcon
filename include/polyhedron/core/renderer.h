#ifndef renderer_h
#define renderer_h

#include <memory>

#include <GLFW/glfw3.h>

#include <polyhedron/core/program.h>
#include <polyhedron/core/transform.h>
#include <polyhedron/core/camera.h>

namespace polyhedron {

class Renderer {
public:
    unsigned int width;
    unsigned int height;
    glm::vec4 clearColor = glm::vec4(0.0);

    bool isDebug = true;
    bool autoClear = true;
    bool depthTest = true;
    bool stencilTest = false;

    GLFWwindow* window;
    float elapsedTime = 0.0;

    std::shared_ptr<Transform> scene;
    std::shared_ptr<Camera> camera;

    Renderer(unsigned int width, unsigned int height);
    Renderer(unsigned int width, unsigned int height, bool isDebug);

    void run(void (*f)(Renderer &renderer));
    void render();
    void terminate();

private:
    void resize();
};

}

#endif
