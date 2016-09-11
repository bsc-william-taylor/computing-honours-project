
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Device.h"


namespace raster
{
    class CL_Context : public JsObject<CL_Context> {
        static v8::Persistent<v8::ObjectTemplate> objectTemplate;
        static v8::Persistent<v8::Function> constructor;
        cl::Context context;
    public:
        CL_Context(CL_Device * device);
        ~CL_Context();

        cl::Context& getContext()
        {
            return context;
        }


        static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
        static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);
    };

}