#ifndef THREADLOCALSTORAGE_HPP
#define THREADLOCALSTORAGE_HPP

#include<SDL2/SDL_thread.h>

class ThreadLocalStorage
{
private:
	SDL_TLSID id;
public:
	ThreadLocalStorage()
	{
		id = SDL_TLSCreate();
	}
	void *get()
	{
		return SDL_TLSGet(id);
	}
	void set(void *data)
	{
		SDL_TLSSet(id,data,[](void*){});
	}
};

#endif // THREADLOCALSTORAGE_HPP
