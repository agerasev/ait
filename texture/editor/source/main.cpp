#include<iostream>
#include<string>

#include"glwindow.h"
#include"editor.h"
using namespace std;

int main(int argc, char *argv[]) {
    Editor editor;
    if(argc > 1) {
        string str(argv[1]);
        if(str == string("-h") || str == string("--help")) {
            cout << "usage:\n" <<
                    "new image:\t -n <filename> <width> <height>\n" <<
                    "open image:\t -o <filename>\n" << endl;
			return 0;
        } else if(str == "-o") {
            if(argc > 2) {
                editor.open(argv[2]);
            } else {
                cout << "invalid arguments" << endl;
                return 0;
            }
        } else if(str == "-n") {
            if(argc > 4) {
                editor.create(argv[2],atoi(argv[3]),atoi(argv[4]));
            } else {
                cout << "invalid arguments" << endl;
                return 0;
            }
        } else {
            cout << "unknown option. use -h to help" << endl;
            return 0;
        }
    } else {
        cout << "too few options. use -h to help" << endl;
        return 0;
    }
    GLWindow window("TriEditor",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
    window.setListener(&editor);
    window.setRenderer(&editor);
    window.start();
    return 0;
}
