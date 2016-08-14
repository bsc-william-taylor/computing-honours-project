
#include "JsPlatform.h"

std::vector<std::function<bool(SDL_Event)>> JsPlatform::eventHooks;

void JsPlatform::CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime)
{

};

void JsPlatform::CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task)
{

};


void JsPlatform::CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds)
{

};

double JsPlatform::MonotonicallyIncreasingTime()
{ 
    return SDL_GetTicks(); 
}

bool JsPlatform::PumpMessageLoop(v8::Isolate* isolate)
{
    static std::function<void()> renderMethod = []() {};  
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        for (auto i = 0; i < eventHooks.size(); i++) {
            if (eventHooks[i](e)) {
                eventHooks.erase(eventHooks.begin() + i);
            }
        }

        if (e.type == EVENT_CALLBACK) {
            auto functionPointer = e.user.data1;
            auto function = static_cast<std::function<void()> *>(functionPointer);
            (*function)();
            delete function;
        }

        if (e.type == TIMER_CHANGE)
        {
            auto functionPointer = static_cast<std::function<void()> *>(e.user.data1);
            renderMethod = *functionPointer;
            //fps = 1.0e9 / *static_cast<int *>(e.user.data2);
            delete functionPointer;
        }
    }

    renderMethod();
    return eventHooks.size() != 0;
}

void JsPlatform::hookEventLoop(std::function<bool(SDL_Event)> callback) {
    eventHooks.push_back(callback);
}