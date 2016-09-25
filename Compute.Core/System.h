
#pragma once

#include "RasterCore.h"

namespace compute
{
    namespace system
    {
        void battery(const v8::FunctionCallbackInfo<v8::Value>& args);
        void exit(const v8::FunctionCallbackInfo<v8::Value>& args);
    }

    void registerSystem(v8::Local<v8::Object>& object);
}