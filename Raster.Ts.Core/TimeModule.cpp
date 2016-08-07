
#include "JsRuntime.h"
#include "TimeModule.h"

#define TIMEOUT_EVENT SDL_USEREVENT + 3

void raster::timeout(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
	callback.Reset(v8::Isolate::GetCurrent(), args[1].As<v8::Function>());

	auto timerCallback = [](Uint32 timeout, void *param) -> Uint32 {
		SDL_Event e;
		e.type = TIMEOUT_EVENT;
		SDL_PushEvent(&e);
		return 0;
	};
	
	SDL_AddTimer(args[0]->ToInteger()->Value(), timerCallback, nullptr);

	JavaScriptSubsystem::hookEventLoop([=](SDL_Event e) {
		if(e.type == TIMEOUT_EVENT) {
			auto javascriptHandler = callback.Get(v8::Isolate::GetCurrent());
			javascriptHandler->Call(javascriptHandler, 0, nullptr);
			return true;
		} 

		return false;
	});
}

void raster::pause(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	int delayTime = args[0]->ToInteger()->Value();

	if (delayTime >= 0)
	{
		SDL_Delay(delayTime);
	}
}