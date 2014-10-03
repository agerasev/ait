#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_thread.h>

class Runnable {
public:
    virtual void run() = 0;
};

class Thread
{
public:
    enum Priority {
        LOW,
        NORMAL,
        HIGH
    };

private:
    Runnable *runnable;
    SDL_Thread *thread;
    SDL_ThreadPriority priority;
	int status;

    static int pull(void *data)
    {
        Thread *thread = static_cast<Thread*>(data);
        SDL_SetThreadPriority(thread->priority);
        thread->runnable->run();
        return 0;
    }

public:
    Thread(Runnable *r = nullptr, Priority p = NORMAL)
    {
        setTarget(r);
        setPriority(p);
    }
    ~Thread()
    {

    }
    void setTarget(Runnable *r)
    {
        runnable = r;
    }

    void setPriority(Priority p)
    {
        switch(p) {
        case LOW:
            priority = SDL_THREAD_PRIORITY_LOW;
            break;
        case NORMAL:
            priority = SDL_THREAD_PRIORITY_NORMAL;
            break;
        case HIGH:
            priority = SDL_THREAD_PRIORITY_HIGH;
            break;
        }
    }

    void start()
    {
		if(runnable == nullptr) {return;}
        thread = SDL_CreateThread(pull,"SDL Thread",static_cast<void*>(this));
    }

    int join()
    {
		SDL_WaitThread(thread,&status);
		return status;
    }
};
