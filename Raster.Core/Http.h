
#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster
{
    namespace http
    {
        void httpPost(const v8::FunctionCallbackInfo<v8::Value>& args);
        void httpGet(const v8::FunctionCallbackInfo<v8::Value>& args);
    }

    void registerHttp(v8::Local<v8::Object>& object);
}