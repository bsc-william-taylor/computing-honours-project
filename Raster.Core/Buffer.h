
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Device.h"
#include "Context.h"


namespace raster
{
    class CL_Buffer : public JsObject<CL_Buffer> {
        static v8::Persistent<v8::ObjectTemplate> objectTemplate;
        static v8::Persistent<v8::Function> constructor;
        cl::Buffer buffer;
        int size;
    public:
        CL_Buffer(CL_Context * context, int memSetting, int size);
        ~CL_Buffer();


        cl::Buffer& getBuffer()
        {
            return buffer;
        }

        static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
        static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);
    };

}