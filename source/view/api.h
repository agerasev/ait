#ifndef API_H
#define API_H

#include<SDL2/SDL.h>

class API {
private:
    API() {}
    static void initSDL() {
        SDL_Init(SDL_INIT_VIDEO);
    }
    static void quitSDL() {
        SDL_Quit();
    }

public:
    static void init() {
        initSDL();
    }
    static void quit() {
        quitSDL();
    }
};

#endif // API_H
