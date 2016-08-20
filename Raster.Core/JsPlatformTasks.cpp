
#include "JsPlatformTasks.h"
#include "JsRuntime.h"

using namespace raster;

JsAwaitTask::JsAwaitTask(std::function<bool(SDL_Event&e)> callback) : 
    action(callback)
{
}

JsAwaitTask::~JsAwaitTask()
{
}

void JsAwaitTask::Run()
{
    auto& platform = JsRuntime::GetPlatform();
    auto insert = true;

    for (auto& e : platform.GetSystemEvents())
    {
        if (action(e))
        {
            insert = false;
        }
    }

    if(insert)
    {
        platform.ReinsertTask({ this, true });
    }
}


JsAsyncTask::JsAsyncTask(std::function<void()> action) : 
    task(action)
{
}

JsAsyncTask::~JsAsyncTask()
{
}

void JsAsyncTask::Run()
{
    if (task != nullptr)
    {
        task();
    }
}

JsRepeatTask::JsRepeatTask(std::function<void()> action) :
    task(action)
{
}

JsRepeatTask::~JsRepeatTask()
{
}

void JsRepeatTask::Run()
{
    auto& platform = JsRuntime::GetPlatform();
    if (task != nullptr)
    {
        platform.ReinsertTask({ this, false });
        task();
    }
}