
#pragma once


#include "RasterCore.h"
#include "JsPlatformTasks.h"

class JsPlatform : public v8::Platform
{
    static std::vector<v8::Task*> tasks;
public:
    void CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds) override;
    void CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime) override;
    void CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task) override;

    double MonotonicallyIncreasingTime() override;

    static bool PumpMessageLoop(v8::Isolate* isolate);
};