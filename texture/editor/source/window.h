#ifndef WINDOW_H
#define WINDOW_H

#include<SDL2/SDL.h>

class Window {
public:
    struct Size {
        int w,h;
        Size() {}
        Size(int aw, int ah) {
            w = aw;
            h = ah;
        }
        Size(const Size &s) {
            w = s.w;
            h = s.h;
        }
    };

    class Listener {
    private:
        SDL_Event event;
    public:
        Listener() {}
        virtual ~Listener() {}
        virtual void handle(const SDL_Event &event) = 0;
    };

    class Renderer {
    public:
        Renderer() {}
        virtual ~Renderer() {}
        virtual void init() = 0;
        virtual void resize(const Size &s) = 0;
        virtual void dispose() = 0;
        virtual void display() = 0;
    };

protected:
    SDL_Window *window;
    Size size;
    Listener *listener = nullptr;
    Renderer *renderer = nullptr;
    bool quit = false;

public:
    Window(const char *name = "SDL Window", const Size &s = Size(800,600), unsigned int flags = 0);
    virtual ~Window();
    Size getSize() const;
    void setListener(Listener *l);
    Listener *getListener();
    void setRenderer(Renderer *r);
    Renderer *getRenderer();
    SDL_Window *getSDLWindow();

private:
    virtual void flip() = 0;
    virtual void resize(const Size &s) = 0;
    void handle();

public:
    void start();
};

#endif // WINDOW_H
