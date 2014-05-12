#include<iostream>

#include"view/window/glwindow.h"

int main() {
    GLWindow window("AIT",800,600);
    bool done = false;
    SDL_Event event;
    while(!done) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                done = true;
            }
        }
        window.clear();
        window.flip();
    }
	return 0;
}
