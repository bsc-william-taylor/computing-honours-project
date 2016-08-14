
#pragma once


#include "RasterCore.h"

#define EVENT_CALLBACK SDL_USEREVENT + 1
#define TIMER_CHANGE SDL_USEREVENT + 2

class JsPlatform : public v8::Platform
{
private:
    static std::vector<std::function<bool(SDL_Event)>> eventHooks;
public:
    /**
    * Schedules a task to be invoked on a background thread. |expected_runtime|
    * indicates that the task will run a long time. The Platform implementation
    * takes ownership of |task|. There is no guarantee about order of execution
    * of tasks wrt order of scheduling, nor is there a guarantee about the
    * thread the task will be run on.
    */
    void CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime);

    /**
    * Schedules a task to be invoked on a foreground thread wrt a specific
    * |isolate|. Tasks posted for the same isolate should be execute in order of
    * scheduling. The definition of "foreground" is opaque to V8.
    */
    void CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task);

    /**
    * Schedules a task to be invoked on a foreground thread wrt a specific
    * |isolate| after the given number of seconds |delay_in_seconds|.
    * Tasks posted for the same isolate should be execute in order of
    * scheduling. The definition of "foreground" is opaque to V8.
    */
    void CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds);

    double MonotonicallyIncreasingTime();

    static bool PumpMessageLoop(v8::Isolate* isolate);
    static void hookEventLoop(std::function<bool(SDL_Event)> callback);
};