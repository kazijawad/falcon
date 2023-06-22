#ifndef window_h
#define window_h

#include <falcon/falcon.h>

namespace falcon {

class RenderWindow {
public:
    GLFWwindow* window;

    RenderWindow() : window(nullptr) {};
    RenderWindow(GLFWwindow* window, Renderer* renderer);

    ~RenderWindow();

    void getSize(int* width, int* height) const;
    void getCursor(double* x, double* y) const;

    void setOrbitControls(OrbitControls* controls);

    void handleResize(int width, int height);
    void handleMouseButton(int button, int action);
    void handleMouseMove(double x, double y);

private:
    struct Attachments {
        Renderer* renderer = nullptr;
        OrbitControls* controls = nullptr;
    } attachments;
};

}

#endif
