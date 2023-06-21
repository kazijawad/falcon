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
    static constexpr int SAMPLES_PER_PIXEL = 4;

    RenderWindow* renderWindow = nullptr;

    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

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

    void handleResize(int width, int height);

private:
    unsigned int width;
    unsigned int height;

    bool needsUpdate = true;

    RenderState state;

    void updateRenderState(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera);
};

}

#endif
