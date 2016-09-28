
#include "System.h"
#include "JsExtensions.h"

void battery(v8::FunctionArgs args)
{
    auto secs{ 0 }, pct{ 0 };
    auto status = SDL_GetPowerInfo(&secs, &pct);
    auto object = v8::Object::New(args.GetIsolate());

    AttachNumber(object, "percentage", pct);
    AttachNumber(object, "seconds", secs);
    AttachNumber(object, "status", status);

    args.GetReturnValue().Set(object);
}

void exit(v8::FunctionArgs args)
{
    if (args.Length() == 1 && args[0]->IsNumber())
    {
        exit(args[0].As<v8::Number>()->Value());
    }

    exit(0);
}

void compute::registerSystem(v8::Exports exports)
{
    AttachFunction(exports, "battery", battery);
    AttachFunction(exports, "exit", exit);

    AttachString(exports, "osArchitecture", Poco::Environment::osArchitecture());
    AttachString(exports, "osVersion", Poco::Environment::osVersion());
    AttachString(exports, "osName", Poco::Environment::osName());

    AttachNumber(exports, "cpuCacheLineSize", SDL_GetCPUCacheLineSize());
    AttachNumber(exports, "systemRam", SDL_GetSystemRAM());
    AttachNumber(exports, "cpuCount", SDL_GetCPUCount());

    AttachBoolean(exports, "hasAltiVec", SDL_HasAltiVec());
    AttachBoolean(exports, "hasRDTSC", SDL_HasRDTSC());
    AttachBoolean(exports, "has3DNow", SDL_Has3DNow());
    AttachBoolean(exports, "hasSSE41", SDL_HasSSE41());
    AttachBoolean(exports, "hasSSE42", SDL_HasSSE42());
    AttachBoolean(exports, "hasAVX2", SDL_HasAVX2());
    AttachBoolean(exports, "hasSSE3", SDL_HasSSE3());
    AttachBoolean(exports, "hasSSE2", SDL_HasSSE2());
    AttachBoolean(exports, "hasMMX", SDL_HasMMX());
    AttachBoolean(exports, "hasAVX", SDL_HasAVX());
    AttachBoolean(exports, "hasSSE", SDL_HasSSE());
}