
#include "JsPlatformTasks.h"

JsAwaitTask::JsAwaitTask(std::function<bool(SDL_Event&e)> callback) : 
    action(callback)
{
}

JsAwaitTask::~JsAwaitTask()
{
}

bool JsAwaitTask::operator()(SDL_Event& e) const 
{ 
    return action(e); 
}

void JsAwaitTask::Run()
{
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
    if (task != nullptr)
    {
        task();
    }
}