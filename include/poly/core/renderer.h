#ifndef renderer_h
#define renderer_h

#include <memory>

#include <GLFW/glfw3.h>

#include <poly/core/program.h>
#include <poly/core/transform.h>
#include <poly/core/camera.h>

namespace poly {

class Renderer {
public:
    unsigned int width;
    unsigned int height;
    bool isDebug;
    float elapsedTime = 0.0;

    GLFWwindow* window;

    std::shared_ptr<Transform> scene;
    std::shared_ptr<Camera> camera;

    Renderer(unsigned int width, unsigned int height);
    Renderer(unsigned int width, unsigned int height, bool isDebug);

    void setClearColor(float r, float g, float b, float a);

    void run(void (*f)(Renderer &renderer));
    void render(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera);
    void terminate();

private:
    float clearColor[4] { 0.0, 0.0, 0.0, 1.0 };
};

}

#endif
