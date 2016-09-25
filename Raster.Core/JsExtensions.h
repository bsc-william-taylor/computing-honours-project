
#pragma once

#include "RasterCore.h"

namespace raster
{
    class JsRuntime;
}

namespace v8
{
    using PersistentCopyable = Persistent<Function, CopyablePersistentTraits<Function>>;
    using FunctionArgs = const FunctionCallbackInfo<Value>&;

    Local<Function> GetFunction(Local<Value> value);
    std::string GetString(Local<Value> value);
    int GetNumber(Local<Value> value);

    void AttachFunction(Local<Object>& obj, std::string key, FunctionCallback function);
    void AttachBoolean(Local<Object>& obj, std::string key, SDL_bool boolean);
    void AttachNumber(Local<Object>& obj, std::string key, int number);
    void AttachString(Local<Object>& obj, std::string key, std::string str);

    void Throw(const FunctionCallbackInfo<Value>& args, std::string msg);
    void CatchExceptions(TryCatch& trycatch);
    void Run(Task* task);

    Local<v8::String> NewString(std::string value);
    Local<Object> WrapPointer(void* pointer);

    template<typename TaskType, typename Lambda, typename ...Args>
    void OnForeground(Lambda functor, Args... args)
    {
        auto& platform = raster::JsRuntime::getPlatform();
        auto task = new TaskType([=] { functor(args...); });
        platform.CallOnForegroundThread(task);
    }

    template<typename TaskType, typename Lambda, typename ...Args>
    void OnBackground(Lambda functor, Args... args)
    {
        auto& platform = raster::JsRuntime::getPlatform();
        auto task = new TaskType([=] { functor(args...); });
        platform.CallOnBackgroundThread(task, v8::Platform::ExpectedRuntime::kLongRunningTask);
    }
}