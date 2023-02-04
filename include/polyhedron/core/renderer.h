#ifndef renderer_h
#define renderer_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

struct RenderState {
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Light>> lights;
};

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    GLFWwindow* window;

    unsigned int getWidth();
    unsigned int getHeight();
    float getAspectRatio();

    void setClearColor(float r, float g, float b, float a);

    void clearColor();
    void clearDepth();
    void clearStencil();
    void clear(bool color = true, bool depth = true, bool stencil = true);

    void run(std::function<void()> fn);

    void render(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera);

    void terminate();

private:
    unsigned int width;
    unsigned int height;

    RenderState state;

    bool handleResize();
    void updateRenderState(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera);
};

}

#endif
