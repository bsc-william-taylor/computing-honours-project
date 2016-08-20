
#pragma once


#include "RasterCore.h"
#include "JsPlatformTasks.h"

class JsPlatform : public v8::Platform
{
    // Pair = Task to run / Is it a skippable event
    std::vector<std::pair<v8::Task*, bool>> tasksToInsert;
    std::vector<v8::Task*> platformTasks;
    std::vector<SDL_Event> events;
public:
    JsPlatform() = default;
    ~JsPlatform() = default;

    std::vector<SDL_Event>& GetSystemEvents() { return events; }
    
    void CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds) override;
    void CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime) override;
    void CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task) override;
    void ReinsertTask(std::pair<v8::Task*, bool>);

    double MonotonicallyIncreasingTime() override;

    bool PumpMessageLoop(v8::Isolate* isolate);
};