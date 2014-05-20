#ifndef RENDERER_H
#define RENDERER_H

#include"../model/imap.h"
#include"window/window.h"

class Renderer : public Window::Renderer {
public:
    Renderer();
    virtual ~Renderer();
    virtual void render();
};

#endif // RENDERER_H
