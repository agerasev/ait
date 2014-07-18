#ifndef WINDOW_HPP
#define WINDOW_HPP

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

    class Render {
    public:
        Render() {}
        virtual ~Render() {}
		virtual int init() = 0;
        virtual void resize(const Size &s) = 0;
        virtual void dispose() = 0;
        virtual void display() = 0;
    };

protected:
    SDL_Window *window;
    Size size;
    Listener *listener = nullptr;
    Render *render = nullptr;
    bool quit = false;

public:
    Window(const char *name = "SDL Window", const Size &s = Size(800,600), unsigned int flags = 0);
    virtual ~Window();
    Size getSize() const;
    void setListener(Listener *l);
    Listener *getListener();
    void setRender(Render *r);
    Render *getRender();
    SDL_Window *getSDLWindow();

private:
    virtual void flip() = 0;
    virtual void resize(const Size &s) = 0;
    void handle();

public:
	int start();
};

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
void Window::setRender(Render *r) {
    render = r;
}
Window::Render *Window::getRender() {
    return render;
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
                if(render != nullptr) {
                    render->resize(getSize());
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

int Window::start() {
    quit = false;
    if(render != nullptr) {
		int rv = 0;
		if((rv = render->init()) != 0) {
			return rv;
		}
        render->resize(size);
    }
    while(!quit) {
        handle();
        if(render != nullptr) {
            render->display();
        }
        flip();
    }
    if(render != nullptr) {
        render->dispose();
    }
	return 0;
}

#endif // WINDOW_HPP
