#include<iostream>

#include"asarone/window/glwindow.hpp"

#include<SDL2/SDL.h>

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    GLWindow window("AIT",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
    window.start();

    SDL_Quit();

	return 0;
}
