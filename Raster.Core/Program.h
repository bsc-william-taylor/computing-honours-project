
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Device.h"
#include "Context.h"

namespace raster
{
    class CL_Program : public JsObject<CL_Program>
    {
        static v8::Persistent<v8::ObjectTemplate> objectTemplate;
        static v8::Persistent<v8::Function> constructor;
        cl::Program program;
    public:
        CL_Program(CL_Context * device, std::string source);
        ~CL_Program();

        cl::Program& getProgram()
        {
            return program;
        }

        static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
        static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);
        static void build(const v8::FunctionCallbackInfo<v8::Value>& build);
    };

}