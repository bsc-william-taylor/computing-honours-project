
#include "JsPlatformTasks.h"
#include "JsRuntime.h"

using namespace raster;

JsAwaitTask::JsAwaitTask(std::function<bool(SDL_Event&e)> callback) : 
    action(callback)
{
}

JsAwaitTask::JsAwaitTask(const JsAwaitTask& copy)
    : JsAwaitTask(copy.action)
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
            break;
        }
    }

    if(insert)
    {
        platform.CallOnForegroundThread({ new JsAwaitTask(*this), true });
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

JsRepeatTask::JsRepeatTask(const JsRepeatTask& copy)
    : JsRepeatTask(copy.task)
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
        platform.CallOnForegroundThread({ new JsRepeatTask(*this), false });
        task();
    }
}