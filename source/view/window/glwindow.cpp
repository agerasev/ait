#include "glwindow.h"

#include "window.h"

#include <GL/glew.h>

#include <iostream>

using namespace std;

GLWindow::GLWindow(const char *name, const Size &s, unsigned int flags) :
    Window(name,s,SDL_WINDOW_OPENGL|flags) {

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
    glViewport(0,0,s.w,s.h);
}
GLWindow::~GLWindow() {
    SDL_GL_DeleteContext(context);
}
void GLWindow::flip() {
    SDL_GL_SwapWindow(window);
    //SDL_Delay(16);
}
void GLWindow::resize(const Size &s) {
    size = s;
    glViewport(0,0,s.w,s.h);
}
