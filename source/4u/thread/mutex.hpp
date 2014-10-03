#ifndef MUTEX_HPP
#define MUTEX_HPP

#include<SDL2/SDL.h>
#include<SDL2/SDL_thread.h>
#include<SDL2/SDL_mutex.h>

class Mutex
{
private:
    SDL_mutex *mtx;

public:
    inline Mutex()
    {
		mtx = SDL_CreateMutex();
    }

    inline ~Mutex()
    {
		SDL_DestroyMutex(mtx);
    }

    inline void lock()
    {
		SDL_LockMutex(mtx);
    }

    inline void unlock()
    {
		SDL_UnlockMutex(mtx);
    }

    inline void tryLock()
    {
		SDL_TryLockMutex(mtx);
    }
};

#endif // MUTEX_HPP
