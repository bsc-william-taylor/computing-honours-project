
#include "JsPlatform.h"

std::vector<v8::Task*> JsPlatform::tasks;

void JsPlatform::CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime)
{
    tasks.push_back(task);
};

void JsPlatform::CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task)
{
    tasks.push_back(task);
};


void JsPlatform::CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds)
{
    tasks.push_back(task);
};

double JsPlatform::MonotonicallyIncreasingTime()
{ 
    return SDL_GetTicks(); 
}

bool JsPlatform::PumpMessageLoop(v8::Isolate* isolate)
{  
    std::vector<SDL_Event> events;

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) 
    {
        events.push_back(e);
    }

    for (auto i = 0; i < tasks.size(); ++i)
    {
        const auto task = static_cast<JsBaseTask *>(tasks[i]);

        if(task != nullptr)
        {
            task->TakeEvents(events);
            task->TakeTasks(tasks);
            task->Run();

            delete task;
            tasks.erase(tasks.begin() + i);
        }
        /*
        const auto repeatTask = dynamic_cast<JsRepeatTask *>(tasks[i]);
        const auto awaitTask = dynamic_cast<JsAwaitTask *>(tasks[i]);
        const auto asyncTask = dynamic_cast<JsAsyncTask *>(tasks[i]);

        if(awaitTask != nullptr)
        {
            if((*awaitTask)(e))
            {
                delete awaitTask;
                tasks.erase(tasks.begin() + i);
            }
        }

        if(asyncTask != nullptr)
        {
            asyncTask->Run();
            delete asyncTask;
            tasks.erase(tasks.begin() + i);
        }

        if(repeatTask != nullptr)
        {
            repeatTask->Run();

            // Fix this later
            if(tasks.size() == 1)
            {
                delete repeatTask;
                tasks.erase(tasks.begin() + i);
            }
        }
        */
    }

    return tasks.size() != 0;
}