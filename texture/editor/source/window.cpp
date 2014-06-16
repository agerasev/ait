#include "window.h"

#include<SDL2/SDL.h>

Window::Window(const char *name, const Size &s, unsigned int flags) {
    size = s;
    window = SDL_CreateWindow(
                name,
                SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                size.w, size.h,
                flags
                );
}
Window::~Window() {
    SDL_DestroyWindow(window);
}
Window::Size Window::getSize() const {
    return size;
}
void Window::setListener(Listener *l) {
    listener = l;
}
Window::Listener *Window::getListener() {
    return listener;
}
void Window::setRenderer(Renderer *r) {
    renderer = r;
}
Window::Renderer *Window::getRenderer() {
    return renderer;
}
SDL_Window *Window::getSDLWindow() {
    return window;
}

void Window::handle() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_WINDOWEVENT:
            switch(event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                resize(Size(event.window.data1,event.window.data2));
                if(renderer != nullptr) {
                    renderer->resize(getSize());
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        if(listener != nullptr) {
            listener->handle(event);
        }
    }
}

void Window::start() {
    quit = false;
    if(renderer != nullptr) {
        renderer->init();
        renderer->resize(size);
    }
    while(!quit) {
        handle();
        if(renderer != nullptr) {
            renderer->display();
        }
        flip();
    }
    if(renderer != nullptr) {
        renderer->dispose();
    }
}
