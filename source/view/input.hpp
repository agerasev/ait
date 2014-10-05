#ifndef INPUT_HPP
#define INPUT_HPP

#include<SDL2/SDL.h>

#include<4u/window/window.hpp>

#include<view/spectator.hpp>

class Input : public Window::Listener
{
private:
	Spectator *spect;
public:
	Input(Spectator *sp) :
		spect(sp)
	{

	}
	virtual void handle(const SDL_Event &event) override
	{
		switch(event.type)
		{
		case SDL_MOUSEWHEEL:
			if(event.wheel.y > 0)
			{
				spect->multOri(1.25*unimat2);
			}
			else if(event.wheel.y < 0)
			{
				spect->multOri(0.8*unimat2);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:

			break;
		case SDL_MOUSEBUTTONUP:

			break;
		}
	}
};

#endif // INPUT_HPP
