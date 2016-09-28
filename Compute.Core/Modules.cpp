
#include "Modules.h"
#include "System.h"
#include "DateTime.h"
#include "Console.h"
#include "Display.h"
#include "OpenGL.h"
#include "OpenCL.h"
#include "Http.h"
#include "Fs.h"

std::map<std::string, compute::JsModule> compute::modules::moduleCache = {};
std::map<std::string, compute::JsModuleRegisterCallback> compute::modules::moduleBindings =
{
    {
        { "datetime", [](auto& object) { compute::registerDateTime(object); } },
        { "display", [](auto& object) { compute::registerDisplay(object); } },
        { "console", [](auto& object) { compute::registerConsole(object); } },
        { "system", [](auto& object) { compute::registerSystem(object); } },
        { "opencl", [](auto& object) { compute::registerOpenCL(object); } },
        { "opengl", [](auto& object) { compute::registerOpenGL(object); } },
        { "http", [](auto& object) { compute::registerHttp(object); } },
        { "fs", [](auto& object) { compute::registerFs(object); } }
    }
};

auto parseInternalModulePath(std::string name)
{
    auto path = Poco::Path(cwd);
    path.append("/modules/");
    path.append(name);
    path.setExtension("js");
    return path.toString();
}

auto parseExternalModulePath(std::string name)
{
    auto path = Poco::Path(Poco::Path::current());
    path.append(name);
    path.setExtension("js");
    return path.toString();
}

auto compute::registerCommonJsModules() -> v8::Local<v8::ObjectTemplate>
{
    auto isolate = v8::Isolate::GetCurrent();
    auto moduleTemplate = v8::ObjectTemplate::New(isolate);

    moduleTemplate->Set(v8::NewString("require"), v8::FunctionTemplate::New(isolate, require));
    moduleTemplate->Set(v8::NewString("exports"), v8::ObjectTemplate::New(isolate));
    moduleTemplate->Set(v8::NewString("cpp"), v8::ObjectTemplate::New(isolate));

    return moduleTemplate;
}

auto moduleType(const std::string& path)
{
    if (path.find(".") != std::string::npos || path.find("/") != std::string::npos)
    {
        return compute::ModuleType::External;
    }

    return compute::ModuleType::Internal;
}

auto createScript(v8::Isolate * isolate, std::string module)
{
    std::string filename;

    if (moduleType(module) == compute::ModuleType::Internal)
    {
        filename = parseInternalModulePath(module);
    }
    else
    {
        filename = parseExternalModulePath(module);
    }

    auto script = compute::readFile(filename.c_str());
    script.insert(0, "(function(raster, exports){");
    script.append("})(cpp, exports);");
    return v8::NewString(script);
}

auto compute::releaseModuleCache() -> void
{
    modules::moduleCache.clear();
}

auto compute::require(const v8::FunctionCallbackInfo<v8::Value>& args) -> void
{
    if (args.Length() != 1) 
    {
        args.GetReturnValue().SetUndefined();
        return;
    } 
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto global = context->Global();
    auto moduleName = GetString(args[0]);

    if (modules::moduleCache.find(moduleName) != modules::moduleCache.end())
    {
        const auto module = modules::moduleCache[moduleName].Get(isolate);
        args.GetReturnValue().Set(module);
    }
    else
    {
        auto currentExports = global->Get(v8::String::NewFromUtf8(isolate, "exports"));
        auto currentCpp = global->Get(v8::String::NewFromUtf8(isolate, "cpp"));
        auto exports = v8::Object::New(isolate);
        auto module = v8::Object::New(isolate);
        auto raster = v8::Object::New(isolate);
        auto script = createScript(isolate, moduleName);

        if (modules::moduleBindings.find(moduleName) != modules::moduleBindings.end())
        {
            modules::moduleBindings[moduleName](raster);
        }

        module->Set(v8::NewString("name"), v8::NewString(moduleName));
        module->Set(v8::NewString("exports"), exports);

        global->Set(v8::NewString("exports"), exports);
        global->Set(v8::NewString("module"), module);
        global->Set(v8::NewString("cpp"), raster);

        v8::Script::Compile(context, script).ToLocalChecked()->Run(context);

        global->Set(v8::NewString("exports"), currentExports);
        global->Set(v8::NewString("cpp"), currentCpp);

        modules::moduleCache[moduleName].Reset(v8::Isolate::GetCurrent(), exports);

        args.GetReturnValue().Set(exports);
    }
}