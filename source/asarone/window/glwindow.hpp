#ifndef GLWINDOW_HPP
#define GLWINDOW_HPP

#include "window.hpp"

class GLWindow : public Window {
protected:
    SDL_GLContext context;
public:
    GLWindow(const char *name = "SDL GL Window", const Size &s = Size(800,600), unsigned int flags = 0);
    virtual ~GLWindow();

    virtual void flip();
    virtual void resize(const Size &s);
};

#include <GL/glew.h>

#include <iostream>

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
		std::cerr << "Error: " << glewGetErrorString(glew_status) << std::endl;
        return;
    }
    if(!GLEW_VERSION_2_0)
    {
		/* TODO:
		 * in this case use old OpenGL */
		std::cerr << "No support for OpenGL 2.0 found" << std::endl;
	}

    glClearColor(0, 0, 0, 0);
    glViewport(0,0,s.w,s.h);
}
GLWindow::~GLWindow() {
    SDL_GL_DeleteContext(context);
}

void GLWindow::flip() {
	SDL_GL_SwapWindow(window);
}
void GLWindow::resize(const Size &s) {
    size = s;
	glViewport(0,0,s.w,s.h);
}

#endif // GLWINDOW_HPP
