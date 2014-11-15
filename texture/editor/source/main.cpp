#include<iostream>
#include<string>

#include"api.hpp"
#include"glwindow.hpp"
#include"editor.hpp"
using namespace std;

int main(int argc, char *argv[]) {
	API::init();
	Editor editor;
	if(argc > 1) {
		string str(argv[1]);
		if(str == string("-h") || str == string("--help")) {
			cout << "usage:\n" <<
			"new image:\t -n --new <filename> <width> <height>\n" <<
			"open image:\t -o --open <filename>\n" <<
			"transform image:\t -t --transform <src> <dst> <w> <h>\n" << endl;
			return 0;
		} else if(str == "-o" || str == "--open") {
		if(argc > 2) {
				editor.open(argv[2]);
			} else {
				cout << "invalid arguments" << endl;
				return 0;
			}
		} else if(str == "-n" || str == "--new") {
			if(argc > 4) {
				editor.create(argv[2],atoi(argv[3]),atoi(argv[4]));
			} else {
				cout << "invalid arguments" << endl;
				return 0;
			}
		} else if(str == "-t" || str == "--transform") {
			if(argc > 5) {
				editor.transform(argv[2],argv[3],atoi(argv[4]),atoi(argv[5]));
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
	API::quit();
	return 0;
}
