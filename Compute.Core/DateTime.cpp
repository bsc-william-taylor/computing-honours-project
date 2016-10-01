
#include "JsRuntime.h"
#include "DateTime.h"
#include "JsExtensions.h"

const auto TimeoutID = SDL_USEREVENT + 3;

auto createTimeoutFunction()
{
    return [](auto ms, auto p) -> Uint32
    {
        SDL_Event e;
        e.user.type = TimeoutID;
        e.user.code = *static_cast<long long*>(p);
        SDL_PushEvent(&e);
        delete p;
        return 0;
    };
}

const auto Timeout = [](auto uniqueID, auto callback)
{
    auto& systemEvents = compute::JsRuntime::getPlatform().GetSystemEvents();
    auto* isolate = v8::Isolate::GetCurrent();

    for (auto& e : systemEvents) {
        if (e.user.type == TimeoutID && e.user.code == uniqueID) {
            v8::TryCatch trycatch(isolate);
            auto function = callback.Get(isolate);
            function->Call(function, 0, nullptr);
            CatchExceptions(trycatch);
            return true;
        }
    }

    return false;
};

void timeout(v8::FunctionArgs args)
{
    const auto uniqueID = GetNumber(args[0]);
    const auto ms = GetNumber(args[1]);

    SDL_AddTimer(ms, createTimeoutFunction(), new long long{ uniqueID });

    v8::PersistentCopyable callback;
    callback.Reset(args.GetIsolate(), GetFunction(args[2]));
    v8::OnForeground(Timeout, uniqueID, callback);
}

const auto PauseConvertError = "pause: Error converting arg1 to number";
const auto PauseNoArgError = "pause: Error expected 1 number parameter";

void pause(v8::FunctionArgs args)
{
    if (args.Length() == 1)
    {
        SDL_Delay(GetNumber(args[0], PauseConvertError));
    }
    else
    {
        v8::Throw(PauseNoArgError);
    }
}

void compute::registerDateTime(v8::Exports exports)
{
    AttachFunction(exports, "timeout", timeout);
    AttachFunction(exports, "pause", pause);
}