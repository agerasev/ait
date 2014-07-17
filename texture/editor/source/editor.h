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
    SDL_RWops *rwops = nullptr;
    Window::Size size;
    Uint8 rc = 0x00, gc = 0xff, bc = 0x00;

public:
    Editor() {

    }

    void open(const char *name) {
        rwops = SDL_RWFromFile(name,"rb+");
        bitmap = SDL_LoadBMP_RW(rwops,1);
    }

    void create(const char *name, int w, int h) {
        rwops = SDL_RWFromFile(name,"wb");
        bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,24,0x0000ff,0x00ff00,0xff0000,0x000000);
    }

    void save() {
        if(rwops != nullptr) {
            SDL_SaveBMP_RW(bitmap,rwops,1);
        }
    }

private:
    Uint8 *getPixel(int x, int y) {
        return (Uint8*)bitmap->pixels + y*3*bitmap->w + 3*x;
    }

public:

    // override Listener
    virtual void handle(const SDL_Event &event) {
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT) {
                Uint8 *ptr = getPixel((event.button.x*bitmap->w)/size.w,(event.button.y*bitmap->h)/size.h);
                *(ptr++) = rc;
                *(ptr++) = gc;
                *(ptr++) = bc;
                //*(ptr++) = ac;
            }
        }
    }
    // override Renderer
    virtual void init() {
        glClearColor(1.0f,0.0f,0.0f,0.0f);
    }
    virtual void resize(const Window::Size &s) {
        size = s;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,size.w,size.h,0);
        glMatrixMode(GL_MODELVIEW);
    }
    virtual void dispose() {

    }
    virtual void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        for(int iy = 0; iy < bitmap->h; ++iy) {
            for(int ix = 0; ix < bitmap->w; ++ix) {
                Uint8 *ptr = getPixel(ix,iy);
                float r = *(ptr++)/256.0;
                float g = *(ptr++)/256.0;
                float b = *(ptr++)/256.0;
                //float a = *(ptr++)/256.0;
                glColor3f(r,g,b);
                float pw = (float)size.w/bitmap->w, ph = (float)size.h/bitmap->h;
                glVertex2f(pw*ix,ph*iy);
                glVertex2f(pw*ix,ph*(iy+1));
                glVertex2f(pw*(ix+1),ph*(iy+1));
                glVertex2f(pw*(ix+1),ph*iy);
            }
        }
        glEnd();

        glFlush();
    }
};

#endif // EDITOR_H
