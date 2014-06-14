#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "window.h"

using namespace std;

class GLWindow : public Window {
protected:
    SDL_GLContext context;
public:
    GLWindow(const char *name = "SDL GL Window", const Size &s = Size(800,600), unsigned int flags = 0);
    virtual ~GLWindow();
    virtual void flip();
    virtual void resize(const Size &s);
};

#endif // GLWINDOW_H
