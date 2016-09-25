
#pragma once

#include "RasterCore.h"

namespace compute
{
    enum class ModuleType
    {
        Internal,
        External
    };

    using JsModuleRegisterCallback = std::function<void(v8::Local<v8::Object>&)>;
    using JsModule = v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>>;

    namespace modules
    {
        extern std::map<std::string, JsModuleRegisterCallback> moduleBindings;
        extern std::map<std::string, JsModule> moduleCache;
    }

    v8::Local<v8::ObjectTemplate> registerCommonJsModules();

    void require(const v8::FunctionCallbackInfo<v8::Value>& args);
    void clearCommonJsModules();
}
