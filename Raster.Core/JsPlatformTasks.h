
#pragma once

#include "RasterCore.h"

class JsPlatform;

class JsAwaitTask : public v8::Task
{
    std::function<bool(SDL_Event&)> action;
public:
    explicit JsAwaitTask(std::function<bool(SDL_Event&e)> action);
    JsAwaitTask(const JsAwaitTask& copy);

    virtual ~JsAwaitTask();

    void Run() override;
};

class JsRepeatTask : public v8::Task
{
    std::function<void()> task;
public:
    explicit JsRepeatTask(std::function<void()> action);
    JsRepeatTask(const JsRepeatTask& copy);

    virtual ~JsRepeatTask();

    void Run() override;
};

using AsyncCallbackWithPlatform = std::function<void(JsPlatform& platform)>;
using AsyncCallback = std::function<void()>;

enum JsAsyncType
{
    Multi
};

class JsAsyncTask : public v8::Task
{
    std::function<void(JsPlatform& platform)> taskWithPlatform;
    std::function<void()> task;
public:
    explicit JsAsyncTask(JsAsyncType type, std::function<void(JsPlatform& platform)> action);
    explicit JsAsyncTask(std::function<void()> action);

    virtual ~JsAsyncTask();

    void Run() override;
};
