#include<iostream>

#include<SDL2/SDL.h>

#include"4u/window/glwindow.hpp"
#include"view/render.hpp"
#include"view/input.hpp"

#include"model/map.hpp"
#include"model/generator/generator.hpp"
#include"view/mapview.hpp"

#include"model/config.hpp"

int main(int, char *[]) {

	SDL_Init(SDL_INIT_VIDEO);

	Map map;
	Generator generator(0xabcdef);
	generator.generate(static_cast<MapWriterHandle&>(map));

	GLWindow window("ait",Window::Size(800,600),SDL_WINDOW_RESIZABLE);

	MapView map_view(static_cast<MapReaderHandle&>(map));

	Render render(&map_view);
	Input input(
	  &render,
	  &generator,
	  /* Don't forget to remove! */
	  static_cast<MapWriterHandle*>(&map)
	);

	window.setRender(&render);
	window.setListener(&input);

	window.start();

    SDL_Quit();

	return 0;
}
