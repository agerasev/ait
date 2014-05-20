#ifndef LISTENER_H
#define LISTENER_H

#include<SDL2/SDL.h>

class Listener {
private:
    SDL_Event event;
public:
    bool quit = false;
    Listener() {}
    virtual ~Listener() {}
    virtual void handle(const SDL_Event &event) {}
    void poll() {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            } else {
                handle(event);
            }
        }
    }
};

#endif // LISTENER_H
