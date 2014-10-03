#ifndef GLWINDOW_HPP
#define GLWINDOW_HPP

#include<string>

#include<GL/glew.h>

#include<4u/exception/glexception.hpp>

#include"sdlwindow.hpp"

class GLWindow : public SDLWindow {
private:
    SDL_GLContext context;
public:
	GLWindow(const char *name = "SDL GL Window", const Size &s = Size(800,600), unsigned int flags = 0) throw(GLException)
		: SDLWindow(name,s,SDL_WINDOW_OPENGL|flags)
	{

		context = SDL_GL_CreateContext(getSDLWindow());

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
		SDL_GL_SetSwapInterval(1);

		GLenum glew_status = glewInit();
		if(GLEW_OK != glew_status)
		{
			throw(GLException(reinterpret_cast<const char*>(glewGetErrorString(glew_status))));
		}
		if(!GLEW_VERSION_2_0)
		{
			/* TODO:
			 * in this case use old OpenGL */
			//throw(GLException("No support for OpenGL 2.0 found"));
		}

		glClearColor(0, 0, 0, 0);
		glViewport(0,0,s.w,s.h);
	}
	virtual ~GLWindow()
	{
		SDL_GL_DeleteContext(context);
	}

	SDL_GLContext getContext()
	{
		return context;
	}

	virtual void flip()
	{
		SDL_GL_SwapWindow(getSDLWindow());
	}
	virtual void resize(const Size &s)
	{
		SDLWindow::resize(s);
		glViewport(0,0,s.w,s.h);
	}
};

#endif // GLWINDOW_HPP
