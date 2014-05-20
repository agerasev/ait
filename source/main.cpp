#include<iostream>

#include"view/window/glwindow.h"

int main(int argc, char *argv[]) {
    GLWindow window("AIT",800,600);
    Listener listener;
    window.setListener(&listener);
    Renderer renderer;
    window.setRenderer(&renderer);
    window.start();
	return 0;
}
