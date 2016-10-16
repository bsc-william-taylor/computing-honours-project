
#pragma once

#include "ComputeCore.h"
#include "JsPlatformTasks.h"
#include "JsPlatformStructures.h"

class JsPlatform : public v8::Platform
{
    JsBackgroundThread taskThread;
    JsTaskBuffer taskBuffer;
    JsTaskQueue taskQueue;

    v8::Persistent<v8::Context> context;
    std::vector<SDL_Event> events;
public:
    JsPlatform();
    ~JsPlatform();

    std::vector<SDL_Event>& GetSystemEvents();

    void SetContext(v8::Local<v8::Context> context)
    {
        this->context.Reset(v8::Isolate::GetCurrent(), context);
    }

    void CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay) override;
    void CallOnBackgroundThread(v8::Task* task, ExpectedRuntime runtime) override;
    void CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task) override;
    void CallOnForegroundThread(v8::Task*);

    double MonotonicallyIncreasingTime() override;

    bool PumpMessageLoop(v8::Isolate* isolate);
    bool NoEvents();
};
