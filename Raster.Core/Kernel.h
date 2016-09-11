
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Device.h"
#include "Context.h"
#include "Program.h"

namespace raster
{
    class CL_Kernel : public JsObject<CL_Kernel> {
        static v8::Persistent<v8::ObjectTemplate> objectTemplate;
        static v8::Persistent<v8::Function> constructor;
        cl::Kernel kernel;
    public:
        CL_Kernel(CL_Program * device, std::string kernalName);
        ~CL_Kernel();

        cl::Kernel& getKernel()
        {
            return kernel;
        }

        static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
        static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);

        // Member functions
        static void setArg(const v8::FunctionCallbackInfo<v8::Value>& args);
    };

}