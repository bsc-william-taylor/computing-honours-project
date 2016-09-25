
#include "JsPlatformTasks.h"
#include "JsRuntime.h"
#include "JsPlatform.h"

using namespace raster;

JsAwaitTask::JsAwaitTask(std::function<bool()> callback) :
    action(callback)
{
}

void JsAwaitTask::Run()
{
    if (!action())
    {
        auto& platform = JsRuntime::getPlatform();
        platform.CallOnForegroundThread(new JsAwaitTask(*this));
    }
}


JsAsyncTask::JsAsyncTask(std::function<void()> action) :
    task(action)
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

void JsRepeatTask::Run()
{
    auto& platform = JsRuntime::getPlatform();

    if (task != nullptr)
    {
        platform.CallOnForegroundThread(new JsRepeatTask(*this));
        task();
    }
}