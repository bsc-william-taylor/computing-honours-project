
#include "System.h"


using namespace raster::system;

void raster::system::cpuCacheLineSize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_GetCPUCacheLineSize());
}

void raster::system::cpuCount(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_GetCPUCount());
}

void raster::system::systemRam(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_GetSystemRAM());
}

void raster::system::has3DNow(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_Has3DNow() ? true : false);
}

void raster::system::hasAVX(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasAVX() ? true : false);
}

void raster::system::hasAVX2(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasAVX2() ? true : false);
}

void raster::system::hasAltiVec(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasAltiVec() ? true : false);
}

void raster::system::hasMMX(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasMMX() ? true : false);
}

void raster::system::hasRDTSC(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasRDTSC() ? true : false);
}

void raster::system::hasSSE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE() ? true : false);
}

void raster::system::hasSSE2(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE2() ? true : false);
}

void raster::system::hasSSE3(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE3() ? true : false);
}

void raster::system::hasSSE41(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE41() ? true : false);
}

void raster::system::hasSSE42(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE42() ? true : false);
}

void raster::registerSystem(v8::Local<v8::Object>& object) 
{
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(v8::String::NewFromUtf8(isolate, "cpuCacheLineSize"), v8::Function::New(isolate, cpuCacheLineSize));
    object->Set(v8::String::NewFromUtf8(isolate, "systemRam"), v8::Function::New(isolate, systemRam));
    object->Set(v8::String::NewFromUtf8(isolate, "cpuCount"), v8::Function::New(isolate, cpuCount));

    object->Set(v8::String::NewFromUtf8(isolate, "has3DNow"), v8::Function::New(isolate, has3DNow));
    object->Set(v8::String::NewFromUtf8(isolate, "hasAVX"), v8::Function::New(isolate, hasAVX));
    object->Set(v8::String::NewFromUtf8(isolate, "hasAVX2"), v8::Function::New(isolate, hasAVX2));
    object->Set(v8::String::NewFromUtf8(isolate, "hasAltiVec"), v8::Function::New(isolate, hasAltiVec));
    object->Set(v8::String::NewFromUtf8(isolate, "hasMMX"), v8::Function::New(isolate, hasMMX));
    object->Set(v8::String::NewFromUtf8(isolate, "hasRDTSC"), v8::Function::New(isolate, hasRDTSC));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE"), v8::Function::New(isolate, hasSSE));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE2"), v8::Function::New(isolate, hasSSE2));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE3"), v8::Function::New(isolate, hasSSE3));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE41"), v8::Function::New(isolate, hasSSE41));
    object->Set(v8::String::NewFromUtf8(isolate, "hasSSE42"), v8::Function::New(isolate, hasSSE42));
}