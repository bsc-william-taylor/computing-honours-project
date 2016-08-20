
#pragma once

#include "RasterCore.h"

class JsAwaitTask : public v8::Task
{
    std::function<bool(SDL_Event&)> action;
public:
    explicit JsAwaitTask(std::function<bool(SDL_Event&e)> action);
    virtual ~JsAwaitTask();
 
    void Run() override;
};

class JsRepeatTask : public v8::Task
{
    std::function<void()> task;
public:
    explicit JsRepeatTask(std::function<void()> action);
    virtual ~JsRepeatTask();

    void Run() override;
};

class JsAsyncTask : public v8::Task
{
    std::function<void()> task;
public:
    explicit JsAsyncTask(std::function<void()> action);
    virtual ~JsAsyncTask();

    void Run() override;
};
