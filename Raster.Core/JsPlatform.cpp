
#include "JsPlatform.h"

void JsPlatform::CallOnBackgroundThread(v8::Task* task, ExpectedRuntime expected_runtime)
{
    platformTasks.push_back(task);
};

void JsPlatform::CallOnForegroundThread(v8::Isolate* isolate, v8::Task* task)
{
    platformTasks.push_back(task);
};

void JsPlatform::CallDelayedOnForegroundThread(v8::Isolate* isolate, v8::Task* task, double delay_in_seconds)
{
    platformTasks.push_back(task);
};

double JsPlatform::MonotonicallyIncreasingTime()
{ 
    return SDL_GetTicks(); 
}

void JsPlatform::ReinsertTask(std::pair<v8::Task*, bool> task)
{
    tasksToInsert.push_back(task);
}

bool JsPlatform::PumpMessageLoop(v8::Isolate* isolate)
{  
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) 
    {
        events.push_back(e);
    }

    for (auto i = 0; i < platformTasks.size(); ++i)
    {
        platformTasks[i]->Run();
        platformTasks.erase(platformTasks.begin() + i);
    }

    auto newEvents{ platformTasks.size() };

    for(auto& newTask : tasksToInsert)
    {
        platformTasks.push_back(newTask.first);
        newEvents += newTask.second ? 1 : 0;
    }
    
    tasksToInsert.clear();
    events.clear();

    return newEvents > 0;
}