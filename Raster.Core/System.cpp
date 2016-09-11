
#include "System.h"
#include "JsExtensions.h"

using namespace raster::system;

void raster::system::battery(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto secs{ 0 }, pct{ 0 };
    auto status = SDL_GetPowerInfo(&secs, &pct);
    auto object = v8::Object::New(args.GetIsolate());

    AttachNumber(object, "percentage", pct);
    AttachNumber(object, "seconds", secs);
    AttachNumber(object, "status", status);

    args.GetReturnValue().Set(object);
}

void raster::system::exit(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1 && args[0]->IsNumber())
    {
        ::exit(args[0].As<v8::Number>()->Value());
    }

    ::exit(0);
}

void raster::registerSystem(v8::Local<v8::Object>& object)
{
    AttachString(object, "osArchitecture", Poco::Environment::osArchitecture());
    AttachString(object, "osVersion", Poco::Environment::osVersion());
    AttachString(object, "osName", Poco::Environment::osName());

    AttachNumber(object, "cpuCacheLineSize", SDL_GetCPUCacheLineSize());
    AttachNumber(object, "systemRam", SDL_GetSystemRAM());
    AttachNumber(object, "cpuCount", SDL_GetCPUCount());

    AttachBoolean(object, "hasAltiVec", SDL_HasAltiVec());
    AttachBoolean(object, "hasRDTSC", SDL_HasRDTSC());
    AttachBoolean(object, "has3DNow", SDL_Has3DNow());
    AttachBoolean(object, "hasSSE41", SDL_HasSSE41());
    AttachBoolean(object, "hasSSE42", SDL_HasSSE42());
    AttachBoolean(object, "hasAVX2", SDL_HasAVX2());
    AttachBoolean(object, "hasSSE3", SDL_HasSSE3());
    AttachBoolean(object, "hasSSE2", SDL_HasSSE2());
    AttachBoolean(object, "hasMMX", SDL_HasMMX());
    AttachBoolean(object, "hasAVX", SDL_HasAVX());
    AttachBoolean(object, "hasSSE", SDL_HasSSE());

    AttachFunction(object, "battery", battery);
    AttachFunction(object, "exit", exit);
}