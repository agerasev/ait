#ifndef EDITOR_H
#define EDITOR_H

#include<iostream>

#include"window.h"
#include"glwindow.h"

#include<SDL2/SDL.h>

#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>

class Editor : public Window::Listener, public Window::Renderer {
private:
	SDL_Surface *bitmap = nullptr;
	const char *filename = nullptr;
    Window::Size size;
	Uint8 rc[4] = { 0x00, 0x00, 0x00, 0xff }; // current colors
	Uint8 lc[4] = { 0xff, 0xff, 0xff, 0xff }; // *
	int shades = 8;
	bool left = false, right = false; // mouse buttons

public:
    Editor() {

    }

	void open(const char *name) {
		filename = name;
		bitmap = SDL_LoadBMP(filename);
    }

	void create(const char *name, int w, int h) {
		filename = name;
        bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,24,0x0000ff,0x00ff00,0xff0000,0x000000);
    }

    void save() {
		SDL_SaveBMP(bitmap,filename);
    }

private:
    Uint8 *getPixel(int x, int y) {
        return (Uint8*)bitmap->pixels + y*3*bitmap->w + 3*x;
    }

public:

	// override Listener methods
    virtual void handle(const SDL_Event &event) {
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT) {
				left = true;
            }
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				right = true;
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
		if(event.type == SDL_MOUSEBUTTONUP) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				left = false;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				right = false;
			}
		}
		if(left || right)
		{
			float mx = (float)event.button.x/size.w, my = (float)(size.h - event.button.y)/size.h;
			float fy = my*bitmap->h;
			float fx = mx*(bitmap->w + bitmap->h) - fy;
			int px = (int)fx - (int)fx%2;
			int py = (int)fy;
			px += (int)(0.5*(fx - px) + (fy - py));
			if(px >= 0 && px < bitmap->w && py >= 0 && py < bitmap->h)
			{
				Uint8 *ptr = getPixel(px,py);
				if(left)
				{
					*(ptr++) = lc[0];
					*(ptr++) = lc[1];
					*(ptr++) = lc[2];
					//*(ptr++) = lc[3];
				}
				else if(right)
				{
					*(ptr++) = rc[0];
					*(ptr++) = rc[1];
					*(ptr++) = rc[2];
					//*(ptr++) = rc[3];
				}
			}
		}
    }
	// override Renderer methods
    virtual void init() {
		glClearColor(0.2f,0.2f,0.2f,0.0f);
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
        glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
        for(int iy = 0; iy < bitmap->h; ++iy) {
            for(int ix = 0; ix < bitmap->w; ++ix) {
                Uint8 *ptr = getPixel(ix,iy);
                float r = *(ptr++)/256.0;
                float g = *(ptr++)/256.0;
                float b = *(ptr++)/256.0;
                //float a = *(ptr++)/256.0;
                glColor3f(r,g,b);
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
					glColor3f((1.0/shades)*j,(1.0/(shades-1))*j,(1.0/(shades-1))*j);
					break;
				}
				glVertex2f(0.25*size.w/6.0*i,0.5*size.h + (1.0/shades)*0.5*size.h*(j+1));
				glVertex2f(0.25*size.w/6.0*i,0.5*size.h + (1.0/shades)*0.5*size.h*j);
				glVertex2f(0.25*size.w/6.0*(i+1),0.5*size.h + (1.0/shades)*0.5*size.h*j);
				glVertex2f(0.25*size.w/6.0*(i+1),0.5*size.h + (1.0/shades)*0.5*size.h*(j+1));
			}
		}

		glColor3f(lc[0]/255.0,lc[1]/255.0,lc[2]/255.0);
		glVertex2f(0, 0.5*size.h);
		glVertex2f(0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h);

		glColor3f(rc[0]/255.0,rc[1]/255.0,rc[2]/255.0);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h);
		glVertex2f(0.25*size.w/6.0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.5*size.w/6.0, 0.5*size.h - (1.0/6.0)*0.5*size.h);
		glVertex2f(0.5*size.w/6.0, 0.5*size.h);

		glEnd();

        glFlush();
	}
};

#endif // EDITOR_H
