
#include "JsPlatform.h"
#include "JsExtensions.h"

JsPlatform::JsPlatform()
{
    taskThread.start([&]()
    {
        while (taskQueue.length())
        {
            taskQueue.pop();
        }
    });
}

JsPlatform::~JsPlatform()
{
    taskThread.join();
}

void JsPlatform::CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime)
{
    taskQueue.push(task);
};

std::vector<SDL_Event>& JsPlatform::GetSystemEvents()
{
    return events;
}

void JsPlatform::CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task)
{
    taskBuffer.push(task);
};

void JsPlatform::CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay )
{
    taskBuffer.push(task);
};

double JsPlatform::MonotonicallyIncreasingTime()
{
    return SDL_GetTicks();
}

void JsPlatform::CallOnForegroundThread(v8::Task* task)
{
    taskBuffer.push(task);
}

bool JsPlatform::PumpMessageLoop(v8::Isolate* isolate)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        events.push_back(e);
    }

    auto tasks = taskBuffer.acquire();

    for (auto& task : tasks)
    {
        Run(task);
    }

    events.clear();
    return NoEvents();
}

bool JsPlatform::NoEvents()
{
    return taskBuffer.length() || taskQueue.length();
}