#ifndef INPUT_HPP
#define INPUT_HPP

#include<SDL2/SDL.h>

#include<4u/window/window.hpp>

#include"config.hpp"
#include"spectator.hpp"
#include"render.hpp"

#include<model/generator/generator.hpp>

class Input : public Window::Listener
{
private:
	Render *render;
	
	/* Temporary */
	Generator *generator;
	MapWriterHandle *map_handle;
	
	int pmx, pmy;
	bool lmb = false, mmb = false, rmb = false;

public:
	Input(Render *ren, Generator *gen, MapWriterHandle *mh) :
		render(ren), generator(gen), map_handle(mh)
	{

	}
	virtual void handle(const SDL_Event &event) override
	{
		auto res = render->getResolution();
		int /*w = res.x(),*/ h = res.y();

		Spectator &spect = render->getSpectator();

		switch(event.type)
		{
		case SDL_MOUSEWHEEL:
			if(event.wheel.y > 0)
			{
				if(1.0/spect.getOri().det() >= sqr(vconfig::MIN_ZOOM))
				{
					spect.multOri(1.25*unimat2);
				}
			}
			else if(event.wheel.y < 0)
			{
				if(1.0/spect.getOri().det() <= sqr(vconfig::MAX_ZOOM))
				{
					spect.multOri(0.8*unimat2);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button)
			{
			case SDL_BUTTON_LEFT:
				lmb = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mmb = true;
				break;
			case SDL_BUTTON_RIGHT:
				rmb = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch(event.button.button)
			{
			case SDL_BUTTON_LEFT:
				lmb = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mmb = false;
				break;
			case SDL_BUTTON_RIGHT:
				rmb = false;
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				generator->step(*map_handle);
				break;
			}
		}

		int mx, my;
		SDL_GetMouseState(&mx,&my);
		int dx = mx - pmx, dy = my - pmy;
		if(rmb)
		{
			spect.addPos((spect.getOri()*vconfig::ISOMETRY).invert()*((2.0/h)*vec2(dx,-dy)));
		}
		pmx = mx;
		pmy = my;
	}
};

#endif // INPUT_HPP
