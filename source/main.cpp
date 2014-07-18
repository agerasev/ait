#include<iostream>

#include<asarone/window/glwindow.hpp>
#include"view/render.h"

#include<SDL2/SDL.h>

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

	GLWindow window("ait",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	Render render;
	window.setRender(&render);
	int ok = window.start();

    SDL_Quit();

	return ok;
}
