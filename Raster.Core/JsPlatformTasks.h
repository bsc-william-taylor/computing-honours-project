
#pragma once

#include "RasterCore.h"

class JsPlatform;

class JsAwaitTask : public v8::Task
{
    std::function<bool()> action;
public:
    JsAwaitTask(std::function<bool()> action);
    ~JsAwaitTask() = default;
    void Run() override;
};

class JsRepeatTask : public v8::Task
{
    std::function<void()> task;
public:
    JsRepeatTask(std::function<void()> action);
    ~JsRepeatTask() = default;
    void Run() override;
};

class JsAsyncTask : public v8::Task
{
    std::function<void()> task;
public:
    JsAsyncTask(std::function<void()> action);
    ~JsAsyncTask() = default;
    void Run() override;
};
