#include<iostream>

#include<SDL2/SDL.h>

#include<4u/window/glwindow.hpp>
#include"view/render.hpp"

#include"model/map.hpp"
#include"view/mapview.hpp"

int main(int , char *[]) {

	SDL_Init(SDL_INIT_VIDEO);

	Map map(4,4);

	GLWindow window("ait",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	Render render;
	window.setRender(&render);

	window.start();

    SDL_Quit();

	return 0;
}
