
#pragma once

#include "RasterCore.h"
#include "JsExtensions.h"

namespace compute
{
    namespace console
    {
        void printLine(v8::FunctionArgs args);
        void print(v8::FunctionArgs args);
        void read(v8::FunctionArgs args);
    }

    void registerConsole(v8::Local<v8::Object>& object);
}
