#ifndef window_h
#define window_h

#include <falcon/falcon.h>

namespace falcon {

class RenderWindow {
public:
    GLFWwindow* window;

    RenderWindow() : window(nullptr) {};
    RenderWindow(GLFWwindow* window);

    ~RenderWindow();

    void getSize(int* width, int* height);
    void getCursor(double* x, double* y);
};

}

#endif
