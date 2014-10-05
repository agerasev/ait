#include<iostream>

#include<SDL2/SDL.h>

#include<4u/window/glwindow.hpp>
#include"view/render.hpp"
#include"view/input.hpp"

#include"model/map.hpp"
#include"view/mapview.hpp"

int main(int, char *[]) {

	SDL_Init(SDL_INIT_VIDEO);

	Map map(0,4);

	GLWindow window("ait",Window::Size(800,600),SDL_WINDOW_RESIZABLE);

	MapView map_view(static_cast<MapReaderHandle&>(map));
	Spectator spect;

	Render render(&map_view,&spect);
	Input input(&spect);

	window.setRender(&render);
	window.setListener(&input);

	window.start();

    SDL_Quit();

	return 0;
}
