#ifndef WINDOW_HPP
#define WINDOW_HPP

#include<4u/exception/exception.hpp>
#include"event.hpp"

class Window {
public:
    struct Size {
        int w,h;
        Size() {}
        Size(int aw, int ah) {
            w = aw;
            h = ah;
        }
        Size(const Size &s) {
            w = s.w;
            h = s.h;
        }
    };

    class Listener {
    public:
        Listener() {}
        virtual ~Listener() {}
		virtual void handle(const Event &event) = 0;
    };

    class Render {
    public:
        Render() {}
        virtual ~Render() {}
		virtual void init() throw(Exception) = 0;
        virtual void resize(const Size &s) = 0;
        virtual void dispose() = 0;
        virtual void display() = 0;
    };

private:
    Size size;
    Listener *listener = nullptr;
    Render *render = nullptr;
	bool exited = false;

public:
	Window(const Size &s = Size(800,600))
	{
		size = s;
	}
	virtual ~Window()
	{

	}
	Size getSize() const
	{
		return size;
	}
	void setListener(Listener *l)
	{
		listener = l;
	}
	Listener *getListener()
	{
		return listener;
	}
	void setRender(Render *r)
	{
		render = r;
	}
	Render *getRender(){
		return render;
	}
	void quit()
	{
		exited = true;
	}

	virtual void flip() = 0;
	virtual void handle() = 0;
	virtual void resize(const Size &s)
	{
		size = s;
	}

	int start() throw(Exception)
	{
		exited = false;
		if(render != nullptr) {
			render->init();
			render->resize(size);
		}
		while(!exited) {
			handle();
			if(render != nullptr) {
				render->display();
			}
			flip();
		}
		if(render != nullptr) {
			render->dispose();
		}
		return 0;
	}
};

#endif // WINDOW_HPP
