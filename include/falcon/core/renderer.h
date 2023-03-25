#ifndef renderer_h
#define renderer_h

#include <falcon/falcon.h>

namespace falcon {

struct RenderState {
    int srcBlendFactor = -1;
    int dstBlendFactor = -1;
    bool depthTest = true;
    bool depthMask = true;
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
    void setDepthTest(bool v);
    void setDepthMask(bool v);
    void setBlendFunc(int src, int dst);

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
