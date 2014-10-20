#include<iostream>

#include<SDL2/SDL.h>

#include<4u/window/glwindow.hpp>
#include"view/render.hpp"
#include"view/input.hpp"

#include"model/map.hpp"
#include"model/generator/mapgenerator.hpp"
#include"view/mapview.hpp"

int main(int, char *[]) {

	SDL_Init(SDL_INIT_VIDEO);

	Map map;
	MapGenerator generator(0xabcdef);
	generator.generate(static_cast<MapWriterHandle&>(map));

	GLWindow window("ait",Window::Size(800,600),SDL_WINDOW_RESIZABLE);

	MapView map_view(static_cast<MapReaderHandle&>(map));

	Render render(&map_view);
	Input input(&render,&generator,/*remove!!!*/static_cast<MapWriterHandle*>(&map));

	window.setRender(&render);
	window.setListener(&input);

	window.start();

    SDL_Quit();

	return 0;
}
