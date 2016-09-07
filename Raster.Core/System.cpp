
#include "System.h"

using namespace raster::system;

void raster::system::battery(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    auto secs{0}, pct{0};
    auto status = SDL_GetPowerInfo(&secs, &pct);

    v8::Local<v8::Object> details = v8::Object::New(isolate);
    details->Set(v8::String::NewFromUtf8(isolate, "percentage"), v8::Number::New(isolate, pct));
    details->Set(v8::String::NewFromUtf8(isolate, "status"), v8::Number::New(isolate, status));
    details->Set(v8::String::NewFromUtf8(isolate, "seconds"), v8::Number::New(isolate, secs));

    args.GetReturnValue().Set(details);
}

void raster::system::exit(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if(args.Length() == 1)
    {
        ::exit(args[0].As<v8::Number>()->Value());
    }

    ::exit(0);    
}

#include <Poco/Environment.h>

void raster::registerSystem(v8::Local<v8::Object>& object) 
{
    const auto isolate = v8::Isolate::GetCurrent();
    const auto osArch = Poco::Environment::osArchitecture();
    const auto osVersion = Poco::Environment::osVersion();
    const auto osName = Poco::Environment::osName();

    object->Set(v8::String::NewFromUtf8(isolate, "cpuCacheLineSize"), v8::Number::New(isolate, SDL_GetCPUCacheLineSize()));
    object->Set(v8::String::NewFromUtf8(isolate, "systemRam"), v8::Number::New(isolate, SDL_GetSystemRAM()));
    object->Set(v8::String::NewFromUtf8(isolate, "cpuCount"), v8::Number::New(isolate, SDL_GetCPUCount()));
    object->Set(v8::String::NewFromUtf8(isolate, "osName"), v8::String::NewFromUtf8(isolate, osName.c_str()));
    object->Set(v8::String::NewFromUtf8(isolate, "osVersion"), v8::String::NewFromUtf8(isolate, osVersion.c_str()));
    object->Set(v8::String::NewFromUtf8(isolate, "osArchitecture"), v8::String::NewFromUtf8(isolate, osArch.c_str()));

    object->Set(v8::String::NewFromUtf8(isolate, "battery"), v8::Function::New(isolate, battery));
    object->Set(v8::String::NewFromUtf8(isolate, "exit"), v8::Function::New(isolate, exit));

    object->Set(v8::String::NewFromUtf8(isolate, "hasAltiVec"), v8::Boolean::New(isolate, SDL_HasAltiVec()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasRDTSC"), v8::Boolean::New(isolate, SDL_HasRDTSC()));
    object->Set(v8::String::NewFromUtf8(isolate, "has3DNow"), v8::Boolean::New(isolate, SDL_Has3DNow()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE41"), v8::Boolean::New(isolate, SDL_HasSSE41()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE42"), v8::Boolean::New(isolate, SDL_HasSSE42()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasAVX2"), v8::Boolean::New(isolate, SDL_HasAVX2()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE3"), v8::Boolean::New(isolate, SDL_HasSSE3()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE2"), v8::Boolean::New(isolate, SDL_HasSSE2));
    object->Set(v8::String::NewFromUtf8(isolate, "hasMMX"), v8::Boolean::New(isolate, SDL_HasMMX()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasAVX"), v8::Boolean::New(isolate, SDL_HasAVX()));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE"), v8::Boolean::New(isolate, SDL_HasSSE));
}