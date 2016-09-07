
#include "JsRuntime.h"
#include "DateTime.h"
#include "JsExtensions.h"

const auto TimeoutEvent = SDL_USEREVENT + 3;

using raster::JsRuntime;

void raster::datetime::timeout(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
    callback.Reset(v8::Isolate::GetCurrent(), args[2].As<v8::Function>());

    const auto isolate = v8::Isolate::GetCurrent();
    const auto uniqueID = args[0]->ToInteger()->Value();
    const auto ms = args[1]->ToInteger()->Value();
	const auto timerCallback = [](Uint32 ms, void *p) -> Uint32 {
		SDL_Event e;
		e.user.type = TimeoutEvent;
        e.user.code = *(long long*)(p);
		SDL_PushEvent(&e);
        delete p;
		return 0;
	};

	SDL_AddTimer(ms, timerCallback, new long long{uniqueID});

    std::pair<v8::Task*, bool> pair(new JsAwaitTask([=](SDL_Event e) {
        if (e.user.type == TimeoutEvent && e.user.code == uniqueID) {
            auto function = callback.Get(isolate);

            v8::TryCatch trycatch(isolate);
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
	int delayTime = args[0]->ToInteger()->Value();

	if (delayTime >= 0)
	{
		SDL_Delay(delayTime);
	}
}

void raster::registerDateTime(v8::Local<v8::Object>& object) 
{
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(V8_String("timeout"), v8::Function::New(isolate, datetime::timeout));
    object->Set(V8_String("pause"), v8::Function::New(isolate, datetime::pause));
}