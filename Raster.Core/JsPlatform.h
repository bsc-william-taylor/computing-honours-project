
#pragma once

#include "RasterCore.h"
#include "JsPlatformTasks.h"

using Concurrency::concurrent_vector;
using Concurrency::concurrent_queue;

class JsPlatform : public v8::Platform
{
    std::vector<std::pair<v8::Task*, bool>> tasks;
    std::vector<SDL_Event> events;

    std::atomic<bool> disposeBackgroundThread;
    std::thread backgroundThread;

    concurrent_vector<std::pair<v8::Task*, bool>> buffer;
    concurrent_queue<v8::Task*> queue;
public:
    JsPlatform();
    ~JsPlatform();

    std::vector<SDL_Event>& GetSystemEvents();

    void CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds) override;
    void CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime) override;
    void CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task) override;
    void CallOnForegroundThread(std::pair<v8::Task*, bool>);

    double MonotonicallyIncreasingTime() override;

    bool PumpMessageLoop(v8::Isolate* isolate);
};