#ifndef API_HPP
#define API_HPP

#include<SDL2/SDL.h>
#include<SDL/SDL_image.h>

class API {
private:
    API(){}
public:
    void init() {
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);
    }
    void quit() {
        IMG_Quit();
        SDL_Quit();
    }
};

#endif // API_HPP