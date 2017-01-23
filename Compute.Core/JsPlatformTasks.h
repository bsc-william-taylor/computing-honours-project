
#pragma once

#include "ComputeCore.h"

class JsPlatform;

class JsAwaitTask : public v8::Task
{
    std::function<bool()> action;
public:
    explicit JsAwaitTask(std::function<bool()> action);
    ~JsAwaitTask() = default;
    void Run() override;
};

class JsRepeatTask : public v8::Task
{
    std::function<void()> task;
public:
    explicit JsRepeatTask(std::function<void()> action);
    ~JsRepeatTask() = default;
    void Run() override;
};

class JsAsyncTask : public v8::Task
{
    std::function<void()> task;
public:
    explicit JsAsyncTask(std::function<void()> action);
    ~JsAsyncTask() = default;
    void Run() override;
};
