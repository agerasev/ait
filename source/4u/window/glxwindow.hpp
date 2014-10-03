#ifndef GLXWINDOW_HPP
#define GLXWINDOW_HPP

namespace lib4u
{
#include"window.hpp"
}

#include <GL/glx.h>
#include <GL/gl.h>
#include <unistd.h>
#include <iostream>

class GLXWindow : public lib4u::Window
{
private:
	Display *display;
	Window window;
	GLXContext context;

public:
	GLXWindow(const Size &s = Size(800,600))
		: lib4u::Window(s)
	{
		display = XOpenDisplay(0);

		int nelements;
		GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display), 0, &nelements);

		static int attributeList[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None };
		XVisualInfo *vi = glXChooseVisual(display, DefaultScreen(display),attributeList);

		XSetWindowAttributes swa;
		swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
		swa.border_pixel = 0;
		swa.event_mask = StructureNotifyMask;

		window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, s.w, s.h, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel|CWColormap|CWEventMask, &swa);

		XMapWindow (display, window);

		context = glXCreateContext(display, vi, 0, GL_TRUE);

		glXMakeCurrent (display, window, context);
	}
	virtual ~GLXWindow()
	{
		glXDestroyContext(display, context);
	}

	Display *getDisplay()
	{
		return display;
	}

	Window getGLXWindow()
	{
		return window;
	}

	GLXContext getGLXContext()
	{
		return context;
	}

	virtual void flip()
	{
		glXSwapBuffers (display, window);
	}

	virtual void handle()
	{
		/* TODO: Add quit handling */
	}

	virtual void resize(const Size &s)
	{
		lib4u::Window::resize(s);
		/* TODO: Add resizing */
	}
};

#endif // GLXWINDOW_HPP
