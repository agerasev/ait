#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "window.h"
#include <GL/glew.h>

#include <iostream>

using namespace std;

class GLWindow : public Window
{
protected:
    SDL_GLContext context;
public:
    GLWindow(const char *name, int w, int h) :
        Window(name,w,h,SDL_WINDOW_OPENGL) {

        context = SDL_GL_CreateContext(window);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
        SDL_GL_SetSwapInterval(1);

        GLenum glew_status = glewInit();
        if(GLEW_OK != glew_status)
        {
            cout << "Error: " << glewGetErrorString(glew_status) << endl;
        }

        if(!GLEW_VERSION_2_0)
        {
            cout << "No support for OpenGL 2.0 found" << endl;
        }

        glClearColor(0, 0, 0, 0);
        glViewport(0,0,width,height);
    }
    virtual ~GLWindow() {
        SDL_GL_DeleteContext(context);
    }
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void flip() {
        SDL_GL_SwapWindow(window);
        //SDL_Delay(16);
    }
    void resize(int w, int h) {
        width = w;
        height = h;
        glViewport(0,0,w,h);
    }
};

#endif // GLWINDOW_H
