
#pragma once

#include "RasterCore.h"

class JsBaseTask : public v8::Task
{
public:
    virtual void TakeEvents(std::vector<SDL_Event>& events) = 0;
    virtual void TakeTasks(std::vector<Task*>& tasks) = 0;
};

class JsAwaitTask : public JsBaseTask
{
    std::function<bool(SDL_Event&)> action;
public:
    explicit JsAwaitTask(std::function<bool(SDL_Event&e)> action);
    virtual ~JsAwaitTask();

    bool operator()(SDL_Event& e) const;
    
    void TakeEvents(std::vector<SDL_Event>& events){};
    void TakeTasks(std::vector<Task*>& tasks){};
    void Run() override;
};

class JsRepeatTask : public JsBaseTask
{
    std::function<void()> task;
public:
    explicit JsRepeatTask(std::function<void()> action);
    virtual ~JsRepeatTask();

    void TakeEvents(std::vector<SDL_Event>& events) {};
    void TakeTasks(std::vector<Task*>& tasks) {};
    void Run() override;
};

class JsAsyncTask : public JsBaseTask
{
    std::function<void()> task;
public:
    explicit JsAsyncTask(std::function<void()> action);
    virtual ~JsAsyncTask();

    void TakeEvents(std::vector<SDL_Event>& events) {};
    void TakeTasks(std::vector<Task*>& tasks) {};
    void Run() override;
};
