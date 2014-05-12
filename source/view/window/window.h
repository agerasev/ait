#ifndef WINDOW_H
#define WINDOW_H

#include<SDL2/SDL.h>

class Window
{
protected:
    SDL_Window *window;
    int width, height;
public:
    Window(const char *name = "SDL Window", int w = 800, int h = 600, unsigned int flags = 0) {
        SDL_Init(SDL_INIT_VIDEO);
        width = w;
        height = h;
        window = SDL_CreateWindow(
                    name,
                    SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                    width, height,
                    flags
                    );
    }
    virtual ~Window() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    struct Size {
        int w,h;
        Size(int aw = 0, int ah = 0) {
            w = aw;
            h = ah;
        }
    };
    Size size() {
        return Size(width,height);
    }
};

#endif // WINDOW_H
