#ifndef EDITOR_HPP
#define EDITOR_HPP

#include<iostream>
#include<queue>

#include"window.hpp"
#include"glwindow.hpp"

#include<SDL2/SDL.h>
#include<SDL/SDL_image.h>

#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include"png.hpp"

class Editor : public Window::Listener, public Window::Renderer {
private:
	SDL_Surface *bitmap = nullptr;
	const char *filename = nullptr;
	Window::Size size;
	Uint8 rc[4] = { 0x00, 0x00, 0x00, 0xff }; // current colors
	Uint8 lc[4] = { 0xff, 0xff, 0xff, 0xff }; // *
	int shades = 8;
	bool left = false, right = false, middle = false; // mouse buttons
	bool fill = false, pick = false;
	bool grid = false; // show grid

public:
	Editor() {

	}

	void open(const char *name) {
		filename = name;
		bitmap = loadPNG(name);
		if(bitmap == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
			std::cout << IMG_GetError() << std::endl;
		}
	}

	void create(const char *name, int w, int h) {
		filename = name;
		bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
	}
	
	void transform(const char *src, const char *dst, int w, int h)
	{
		filename = dst;
		bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		SDL_Surface *source = SDL_LoadBMP(src);
		for(int iy = 0; iy < h; ++iy)
		{
			for(int ix = 0; ix < w; ++ix)
			{
				Uint8 *dptr = (Uint8*)bitmap->pixels + iy*bitmap->pitch + 4*ix;
				// float sy = (float)iy/h*source->h, sx = (float)(ix + iy)/(w + h)*source->w;
				int sy = source->h - iy - 1, sx = ix;
				Uint8 *sptr = (Uint8*)source->pixels + (int)sy*source->pitch + source->format->BytesPerPixel*(int)sx;
				if(source->format->BytesPerPixel > 3)
				{
					dptr[0] = sptr[0];
					dptr[1] = sptr[1];
					dptr[2] = sptr[2];
					dptr[3] = sptr[3];
				}
				else
				{
					dptr[0] = sptr[0];
					dptr[1] = sptr[1];
					dptr[2] = sptr[2];
					dptr[3] = 0xff;
				}
			}
		}
	}

	void save() {
		savePNG(filename,bitmap);
	}

private:
	Uint8 *getPixel(int x, int y) {
		return (Uint8*)bitmap->pixels + (bitmap->h - y - 1)*4*bitmap->w + 4*x;
	}

public:

	// override Listener methods
	virtual void handle(const SDL_Event &event) 
	{
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_g)
			{
				grid = !grid;
			}
			if(event.key.keysym.sym == SDLK_f)
			{
				fill = true;
			}
			if(event.key.keysym.sym == SDLK_p)
			{
				pick = true;
			}
		}
		if(event.type == SDL_KEYUP)
		{
			if(event.key.keysym.sym == SDLK_f)
			{
				fill = false;
			}
			if(event.key.keysym.sym == SDLK_p)
			{
				pick = false;
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) 
		{
			if(event.button.button == SDL_BUTTON_LEFT) 
			{
				left = true;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				right = true;
			}
			else if(event.button.button == SDL_BUTTON_MIDDLE)
			{
				middle = true;
			}
			float mx = (float)event.button.x/size.w, my = (float)(size.h - event.button.y)/size.h;
			if(mx < 1.0/6.0 && my > 0.5)
			{
				int kind = (int)(4.0*mx*6.0)%4;
				Uint8 *col = nullptr;
				if(event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
				{
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						col = lc;
					}
					else
					{
						col = rc;
					}
					col[kind] = (int)(2.0*(shades)*(my - 0.5))*0xff/(shades-1);
				}
			}
		}
		if(event.type == SDL_MOUSEBUTTONUP) 
		{
			if(event.button.button == SDL_BUTTON_LEFT) 
			{
				left = false;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				right = false;
			}
			else if(event.button.button == SDL_BUTTON_MIDDLE)
			{
				middle = false;
			}
		}
	}

	// override Renderer methods
	virtual void init() {
		glClearColor(0.2f,0.2f,0.2f,0.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}

	virtual void resize(const Window::Size &s) {
		size = s;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,size.w,0,size.h);
		glMatrixMode(GL_MODELVIEW);
	}

	virtual void dispose() {
		save();
	}

	virtual void display() {
		if(left || right || middle)
		{
			int x, y;
			SDL_GetMouseState(&x,&y);
			float mx = (float)x/size.w, my = (float)(size.h - y)/size.h;
			float fy = my*bitmap->h;
			float fx = mx*(bitmap->w + bitmap->h) - fy;
			int px = (int)fx - (int)fx%2;
			int py = (int)fy;
			px += (int)(0.5*(fx - px) + (fy - py));
			if(px >= 0 && px < bitmap->w && py >= 0 && py < bitmap->h)
			{
				Uint8 *ptr = getPixel(px,py);
				Uint8 *col = nullptr;
				if(left)
				{
					col = lc;
				}
				else if(right)
				{
					col = rc;
				}
				if(col != nullptr)
				{
					if(fill)
					{
						/* fill */
						unsigned r = *((unsigned*)col);
						unsigned c = *((unsigned*)ptr);
						if(c != r)
						{
							std::queue<std::pair<int,int>> next;
							next.push(std::pair<int,int>(px,py));
							while(!next.empty())
							{
								std::pair<int,int> p = next.front();
								next.pop();
								int x = p.first, y = p.second;
								if(x >= 0 && x < bitmap->w && y >= 0 && y < bitmap->h)
								{
									Uint8 *cptr = getPixel(x,y);
									unsigned cc = *((unsigned*)cptr);
									if(c == cc)
									{
										*(unsigned*)cptr = r;
										next.push(std::pair<int,int>(x+1,y));
										next.push(std::pair<int,int>(x-1,y));
										if(x%2)
										{
											next.push(std::pair<int,int>(x-1,y+1));
										}
										else
										{
											next.push(std::pair<int,int>(x+1,y-1));
										}
									}
								}
							}
						}
					}
					else if(pick)
					{
						/* pick a color */
						col[0] = ptr[0];
						col[1] = ptr[1];
						col[2] = ptr[2];
						col[3] = ptr[3];
					}
					else
					{
						/* draw */
						ptr[0] = col[0];
						ptr[1] = col[1];
						ptr[2] = col[2];
						ptr[3] = col[3];
					}
				}
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		for(int iy = 0; iy < bitmap->h; ++iy) {
			for(int ix = 0; ix < bitmap->w; ++ix) {
				Uint8 *ptr = getPixel(ix,iy);
				glColor4ubv(ptr);
				float ph = (float)size.h/bitmap->h;
				float pw = (float)size.w/(bitmap->w + bitmap->h);
				if(ix%2 == 0)
				{
					glVertex2f(pw*(ix + iy), ph*iy);
					glVertex2f(pw*(ix + iy + 2), ph*iy);
					glVertex2f(pw*(ix + iy + 1), ph*(iy + 1));
				}
				else
				{
					glVertex2f(pw*(ix + iy + 1), ph*iy);
					glVertex2f(pw*(ix + iy + 2), ph*(iy + 1));
					glVertex2f(pw*(ix + iy), ph*(iy + 1));
				}

			}
		}
		glEnd();

		glBegin(GL_QUADS);
		for(int i = 0; i < 4; ++i)
		{
			for(int j = 0; j < shades; ++j)
			{
				switch(i)
				{
				case 0:
					glColor3f((1.0/shades)*j,0,0);
					break;
				case 1:
					glColor3f(0,(1.0/shades)*j,0);
					break;
				case 2:
					glColor3f(0,0,(1.0/shades)*j);
					break;
				default:
					glColor4f(1.0,1.0,1.0,(1.0/(shades-1))*j);
					break;
				}
				glVertex2f(0.25*size.w/6.0*i,0.5*size.h + (1.0/shades)*0.5*size.h*(j+1));
				glVertex2f(0.25*size.w/6.0*i,0.5*size.h + (1.0/shades)*0.5*size.h*j);
				glVertex2f(0.25*size.w/6.0*(i+1),0.5*size.h + (1.0/shades)*0.5*size.h*j);
				glVertex2f(0.25*size.w/6.0*(i+1),0.5*size.h + (1.0/shades)*0.5*size.h*(j+1));
			}
		}

		glColor4ubv(lc);
		glVertex2f(0, 0.5*size.h);
		glVertex2f(0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h);

		glColor4ubv(rc);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.5*size.w/6.0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.5*size.w/6.0, 0.5*size.h);

		glEnd();

		if(grid)
		{
			glColor3f(1.0f,0.0f,1.0f);
			glBegin(GL_LINES);
			glVertex2d(0.0,0.0);
			glVertex2d(1.0/3.0*size.w,size.h);
			glVertex2d(1.0/3.0*size.w,size.h);
			glVertex2d(size.w,size.h);
			glVertex2d(0.0,0.0);
			glVertex2d(2.0/3.0*size.w,0.0);
			glVertex2d(2.0/3.0*size.w,0.0);
			glVertex2d(size.w,size.h);
			glVertex2d(1.0/6.0*size.w,0.5*size.h);
			glVertex2d(1.0/3.0*size.w,0.0);
			glVertex2d(1.0/6.0*size.w,0.5*size.h);
			glVertex2d(0.5*size.w,0.5*size.h);
			glVertex2d(1.0/3.0*size.w,0.0);
			glVertex2d(0.5*size.w,0.5*size.h);
			glVertex2d(5.0/6.0*size.w,0.5*size.h);
			glVertex2d(2.0/3.0*size.w,size.h);
			glVertex2d(5.0/6.0*size.w,0.5*size.h);
			glVertex2d(0.5*size.w,0.5*size.h);
			glVertex2d(2.0/3.0*size.w,size.h);
			glVertex2d(0.5*size.w,0.5*size.h);
			glVertex2d(1.0/3.0*size.w,size.h);
			glVertex2d(2.0/3.0*size.w,0.0);
			glEnd();
		}
		glFlush();
	}
};

#endif // EDITOR_H
