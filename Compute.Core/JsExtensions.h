
#pragma once

#include "ComputeCore.h"

namespace compute
{
    class JsRuntime;
}

class JsAwaitTask;

namespace v8
{
    using PersistentCopyable = Persistent<Function, CopyablePersistentTraits<Function>>;
    using FunctionArgs = const FunctionCallbackInfo<Value>&;
    using Exports = Local<Object>;

    Local<TypedArray> GetTypedArray(Local<Value>, std::string err = "");
    Local<Function> GetFunction(Local<Value> value, std::string err = "");
    Local<Object> GetObject(Local<Value> value, std::string err = "");
    Local<Array> GetArray(Local<Value> value, std::string err = "");
    std::string GetString(Local<Value> value, std::string err = "");
    double GetNumber(Local<Value> value, std::string err = "");

    void AttachFunction(Local<Object>& obj, std::string key, FunctionCallback function);
    void AttachBoolean(Local<Object>& obj, std::string key, SDL_bool boolean);
    void AttachNumber(Local<Object>& obj, std::string key, int number);
    void AttachString(Local<Object>& obj, std::string key, std::string str);

    void Throw(std::string msg);
    void CatchExceptions(TryCatch& trycatch);
    void Run(Task* task);

    Local<String> NewString(std::string value);
    Local<Number> NewNumber(int number);

    void* UnwrapPointer(Local<Value> object);
    Local<Object> WrapPointer(void* pointer);

    template<typename T>
    void Return(FunctionArgs& args, T v)
    {
        args.GetReturnValue().Set(v);
    }

    template<typename TaskType, typename Lambda, typename ...Args>
    void OnForeground(Lambda functor, Args... args)
    {
        auto& platform = compute::JsRuntime::getPlatform();
        auto task = new TaskType([=] { functor(args...); });
        platform.CallOnForegroundThread(task);
    }

    template<typename TaskType, typename Lambda, typename ...Args>
    void OnBackground(Lambda functor, Args... args)
    {
        auto& platform = compute::JsRuntime::getPlatform();
        auto task = new TaskType([=] { functor(args...); });
        platform.CallOnBackgroundThread(task, Platform::ExpectedRuntime::kLongRunningTask);
    }

    template<typename Lambda, typename ...Args>
    void OnForeground(Lambda functor, Args... args)
    {
        auto& platform = compute::JsRuntime::getPlatform();
        auto task = new JsAwaitTask([=] { return functor(args...); });
        platform.CallOnForegroundThread(task);
    }

    template<typename Lambda, typename ...Args>
    void OnBackground(Lambda functor, Args... args)
    {
        auto& platform = compute::JsRuntime::getPlatform();
        auto task = new JsAwaitTask([=] { return functor(args...); });
        platform.CallOnBackgroundThread(task, Platform::ExpectedRuntime::kLongRunningTask);
    }
}