
#pragma once

#include "ComputeCore.h"
#include "JsPlatformTasks.h"
#include "JsPlatformStructures.h"

class JsPlatform : public v8::Platform
{
    JsBackgroundThread taskThread;
    JsTaskBuffer taskBuffer;
    JsTaskQueue taskQueue;

    std::vector<SDL_Event> events;
public:
    JsPlatform();
    ~JsPlatform();

    std::vector<SDL_Event>& GetSystemEvents();

    void CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay) override;
    void CallOnBackgroundThread(v8::Task* task, ExpectedRuntime runtime) override;
    void CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task) override;
    void CallOnForegroundThread(v8::Task*);

    double MonotonicallyIncreasingTime() override;

    bool PumpMessageLoop(v8::Isolate* isolate);
    bool NoEvents();
};
