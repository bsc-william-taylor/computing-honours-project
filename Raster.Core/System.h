
#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster 
{
    namespace system
    {
        void cpuCacheLineSize(const v8::FunctionCallbackInfo<v8::Value>& args);
        void systemRam(const v8::FunctionCallbackInfo<v8::Value>& args);
        void cpuCount(const v8::FunctionCallbackInfo<v8::Value>& args);
        
        void hasAltiVec(const v8::FunctionCallbackInfo<v8::Value>& args);
        void has3DNow(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasRDTSC(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasSSE41(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasSSE42(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasSSE2(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasSSE3(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasAVX2(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasAVX(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasMMX(const v8::FunctionCallbackInfo<v8::Value>& args);
        void hasSSE(const v8::FunctionCallbackInfo<v8::Value>& args);
    }

	void registerSystem(v8::Local<v8::Object>& object);
}