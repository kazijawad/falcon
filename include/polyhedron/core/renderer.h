#ifndef renderer_h
#define renderer_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    GLFWwindow* window;

    unsigned int width();
    unsigned int height();
    float aspectRatio();

    void setClearColor(float r, float g, float b, float a);

    void clearColor();
    void clearDepth();
    void clearStencil();
    void clear(bool color = true, bool depth = true, bool stencil = true);

    void run(std::function<void()> fn);

    void render(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera);

    void terminate();

private:
    struct RenderState {
        unsigned int width;
        unsigned int height;
    } state;

    bool handleResize();
    std::vector<std::shared_ptr<Mesh>> getRenderList(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera);
};

}

#endif
