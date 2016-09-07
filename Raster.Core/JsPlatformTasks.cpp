
#include "JsPlatformTasks.h"
#include "JsRuntime.h"
#include "JsPlatform.h"

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
    auto& platform = JsRuntime::getPlatform();
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
    task(action), taskWithPlatform(nullptr)
{
}

JsAsyncTask::JsAsyncTask(JsAsyncType type, std::function<void(JsPlatform& platform)> action) :
    task(nullptr), taskWithPlatform(action)
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

    if (taskWithPlatform != nullptr)
    {
        taskWithPlatform(JsRuntime::getPlatform());
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
    auto& platform = JsRuntime::getPlatform();

    if (task != nullptr)
    {
        platform.CallOnForegroundThread({ new JsRepeatTask(*this), false });
        task();
    }
}