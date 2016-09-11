
#include "JsRuntime.h"
#include "DateTime.h"
#include "JsExtensions.h"

const auto TimeoutEvent = SDL_USEREVENT + 3;

using raster::JsRuntime;

std::pair<bool, std::string> argumentsOkay(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto output = std::pair<bool, std::string>(true, "");

    if (args.Length() != 3)
    {
        output = std::pair<bool, std::string>(false, "Error timeout function takes 3 arguments");
    }

    if (!args[0]->IsNumber())
    {
        output = std::pair<bool, std::string>(false, "Error timeout argument 1 is not a number");
    }

    if (!args[1]->IsNumber())
    {
        output = std::pair<bool, std::string>(false, "Error timeout argument 2 is not a number");
    }

    if (!args[2]->IsFunction())
    {
        output = std::pair<bool, std::string>(false, "Error timeout argument 3 is not a number");
    }

    return output;
}

SDL_TimerCallback createTimeoutFunction()
{
    return [](Uint32, void *p) -> Uint32
    {
        SDL_Event e;
        e.user.type = TimeoutEvent;
        e.user.code = *static_cast<long long*>(p);
        SDL_PushEvent(&e);
        delete p;
        return 0;
    };
}

void raster::datetime::timeout(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Isolate * isolate = args.GetIsolate();
    std::string msg;
    bool okay;

    tie(okay, msg) = argumentsOkay(args);

    if (!okay)
    {
        v8::Throw(args, msg);
        return;
    }

    v8::PersistentCopyable callback;
    callback.Reset(isolate, args[2].As<v8::Function>());

    const auto timerCallback = createTimeoutFunction();
    const auto uniqueID = args[0]->ToInteger()->Value();
    const auto ms = args[1]->ToInteger()->Value();

    SDL_AddTimer(ms, timerCallback, new long long{ uniqueID });

    std::pair<v8::Task*, bool> pair(new JsAwaitTask([=](SDL_Event e) {
        if (e.user.type == TimeoutEvent && e.user.code == uniqueID) {
            v8::TryCatch trycatch(isolate);
            v8::Local<v8::Function> function = callback.Get(isolate);
            function->Call(function, 0, nullptr);
            CatchExceptions(trycatch);
            return true;
        }

        return false;
    }), true);

    JsRuntime::getPlatform().CallOnForegroundThread(pair);
}

void raster::datetime::pause(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1 && args[0]->IsNumber())
    {
        SDL_Delay(args[0]->ToInteger()->Value());
    }
    else
    {
        Throw(args, "Error expected 1 number parameter");
    }
}

void raster::registerDateTime(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "timeout", datetime::timeout);
    AttachFunction(object, "pause", datetime::pause);
}