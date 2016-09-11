#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster
{
    namespace datetime
    {
        void timeout(const v8::FunctionCallbackInfo<v8::Value>& args);
        void pause(const v8::FunctionCallbackInfo<v8::Value>& args);
    }

    void registerDateTime(v8::Local<v8::Object>& object);
}