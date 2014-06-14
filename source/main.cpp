#include<iostream>

#include"view/api.h"
#include"view/window/glwindow.h"

int main(/*int argc, char *argv[]*/) {
    API::init();
    GLWindow window("AIT",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
    window.start();
    API::quit();
	return 0;
}
