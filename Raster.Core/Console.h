
#pragma once

#include "RasterCore.h"

namespace raster
{
    namespace console
    {
        void printLine(const v8::FunctionCallbackInfo<v8::Value>& args);
        void print(const v8::FunctionCallbackInfo<v8::Value>& args);
        void read(const v8::FunctionCallbackInfo<v8::Value>& args);
    }

    void registerConsole(v8::Local<v8::Object>& object);
}
