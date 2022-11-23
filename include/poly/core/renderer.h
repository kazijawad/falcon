#ifndef renderer_h
#define renderer_h

#include <GLFW/glfw3.h>
#include <poly/core/program.h>

namespace poly {

class Renderer {
public:
    unsigned int width;
    unsigned int height;
    bool isDebug;

    GLFWwindow* window;

    Renderer(unsigned int width, unsigned int height);
    Renderer(unsigned int width, unsigned int height, bool isDebug);

    void setClearColor(float r, float g, float b, float a);

    void run(void (*f)(Program program, unsigned int VAO), Program program, unsigned int VAO);
    void terminate();

private:
    float clearColor[4] { 0.0, 0.0, 0.0, 1.0 };
};

}

#endif
