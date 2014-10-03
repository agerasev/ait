#ifndef SDLWINDOW_HPP
#define SDLWINDOW_HPP

#include<SDL2/SDL.h>
#include<4u/exception/exception.hpp>

#include"window.hpp"

class SDLWindow : public Window {
private:
	SDL_Window *window;

public:
	SDLWindow(const char *name = "SDL Window", const Window::Size &size = Window::Size(800,600), unsigned int flags = 0)
		: Window(size)
	{
		window = SDL_CreateWindow(
					name,
					SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
					size.w, size.h,
					flags
					);
	}
	virtual ~SDLWindow()
	{
		SDL_DestroyWindow(window);
	}
	SDL_Window *getSDLWindow()
	{
		return window;
	}

private:
	virtual void handle()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				quit();
				break;
			case SDL_WINDOWEVENT:
				switch(event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					resize(Size(event.window.data1,event.window.data2));
					if(getRender() != nullptr) {
						getRender()->resize(getSize());
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			if(getListener() != nullptr) {
				getListener()->handle(event);
			}
		}
	}
};

#endif // SDLWINDOW_HPP
