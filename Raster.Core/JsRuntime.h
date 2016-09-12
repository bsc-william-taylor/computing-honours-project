#pragma once

#include "RasterCore.h"
#include "JsPlatform.h"

namespace raster
{
    class JsRuntime
    {
        static JsPlatform platform;
    public:
        explicit JsRuntime(std::vector<std::string>& args);
        virtual ~JsRuntime();

        void initialise(std::vector<std::string>& args);
        void start(std::string script = "");

        static JsPlatform& getPlatform();
    private:
        void executeScriptMode(v8::Isolate* isolate, v8::Local<v8::Context> context, v8::Local<v8::String>);
        void executeRepMode(v8::Isolate* isolate, v8::Local<v8::Context> context);
    };
}
