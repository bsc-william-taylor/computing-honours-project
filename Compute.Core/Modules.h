
#pragma once

#include "ComputeCore.h"
#include "JsExtensions.h"

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

    auto registerCommonJsModules() -> v8::Local<v8::ObjectTemplate>;
    auto require(const v8::FunctionCallbackInfo<v8::Value>& args) -> void;
    auto releaseModuleCache() -> void;
}
