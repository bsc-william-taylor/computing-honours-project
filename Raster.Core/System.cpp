
#include "System.h"

void raster::cpuCacheLineSize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_GetCPUCacheLineSize());
}

void raster::cpuCount(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_GetCPUCount());
}

void raster::systemRam(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_GetSystemRAM());
}

void raster::has3DNow(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_Has3DNow() ? true : false);
}

void raster::hasAVX(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasAVX() ? true : false);
}

void raster::hasAVX2(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasAVX2() ? true : false);
}

void raster::hasAltiVec(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasAltiVec() ? true : false);
}

void raster::hasMMX(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasMMX() ? true : false);
}

void raster::hasRDTSC(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasRDTSC() ? true : false);
}

void raster::hasSSE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE() ? true : false);
}

void raster::hasSSE2(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE2() ? true : false);
}

void raster::hasSSE3(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE3() ? true : false);
}

void raster::hasSSE41(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE41() ? true : false);
}

void raster::hasSSE42(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set(SDL_HasSSE42() ? true : false);
}