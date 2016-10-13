
#include "Modules.h"
#include "System.h"
#include "DateTime.h"
#include "Console.h"
#include "Display.h"
#include "OpenGL.h"
#include "OpenCL.h"
#include "Http.h"
#include "Fs.h"
#include "Application.h"

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

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

std::string moduleDirectory = "";
std::string moduleBegin = "(function(compute){ const module = { exports: {} }, exports = module.exports; ";
std::string moduleEnd = " return module.exports;})(cpp);";

auto parseInternalModulePath(std::string name)
{
    auto exeDir = compute::ComputeApp::exeLocation();
    auto path = Poco::Path(exeDir);
    path.append("/modules/");
    path.setFileName(name);
    path.setExtension("js");

    if(!Poco::File(path).exists())
    {
        auto packagePath = Poco::Path(Poco::Path::current());
        packagePath.append("/node_modules/" + name + "/");
        packagePath.setFileName("package");
        packagePath.setExtension("json");

        if(!Poco::File(packagePath).exists())
        {
            return std::string("");
        }

        Poco::JSON::Parser parser;
        Poco::Path npmDirectory;

        auto jsonData = compute::readFile(packagePath.toString());
        auto json = parser.parse(jsonData);
        auto object = json.extract<Poco::JSON::Object::Ptr>();
       
        npmDirectory.append("/node_modules/" + name + "/");
        npmDirectory.append(object->get("main").toString());
        npmDirectory.setFileName("");
        npmDirectory.setBaseName("");
        moduleDirectory = npmDirectory.toString();

        packagePath.setFileName(object->get("main"));
        return packagePath.toString();
    }
    
    return path.toString();
}

auto parseExternalModulePath(std::string name)
{
    auto path = Poco::Path(Poco::Path::current());
    path.append(moduleDirectory.c_str());
    path.setFileName(name);
    path.setExtension("js");
    return path.toString();
}

auto compute::registerCommonJsModules() -> v8::Local<v8::ObjectTemplate>
{
    auto isolate = v8::Isolate::GetCurrent();
    auto exports = v8::ObjectTemplate::New(isolate);
    auto module = v8::ObjectTemplate::New(isolate);
    module->Set(v8::NewString("exports"), exports);

    auto moduleTemplate = v8::ObjectTemplate::New(isolate);
    moduleTemplate->Set(v8::NewString("require"), v8::FunctionTemplate::New(isolate, require));
    moduleTemplate->Set(v8::NewString("exports"), exports);
    moduleTemplate->Set(v8::NewString("cpp"), v8::ObjectTemplate::New(isolate));
    moduleTemplate->Set(v8::NewString("module"), module);
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

    if(filename.empty())
    {
        v8::Throw("Error couldnt load module " + module);
    }

    auto script = compute::readFile(filename.c_str());

    if (script.empty())
    {
        v8::Throw("Error couldnt load module " + filename);
    }

    script.insert(0, moduleBegin);
    script.append(moduleEnd);
    return v8::NewString(script);
}

auto compute::releaseModuleCache() -> void
{
    modules::moduleCache.clear();
}

auto getDirectory(std::string module)
{
    Poco::Path path(module);
    path.setFileName("");
    path.setBaseName("");
    return path.toString();
}

auto compute::require(v8::FunctionArgs args) -> void
{
    if (args.Length() != 1) 
    {
        args.GetReturnValue().SetUndefined();
        return;
    } 

    auto moduleName = GetString(args[0]);
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto global = context->Global();
    
    auto prevDirectory = moduleDirectory;
    auto subDirectory = getDirectory(moduleName);

    if (modules::moduleCache.find(moduleName) != modules::moduleCache.end())
    {
        args.GetReturnValue().Set(modules::moduleCache[moduleName].Get(isolate));
    }
    else
    {
        auto compute = v8::Object::New(isolate);
        auto script = createScript(isolate, moduleName);

        moduleDirectory += subDirectory;

        if (modules::moduleBindings.find(moduleName) != modules::moduleBindings.end())
        {
            modules::moduleBindings[moduleName](compute);
        }

        global->Set(v8::NewString("cpp"), compute);

        auto runnable = v8::Script::Compile(context, script).ToLocalChecked();
        auto exports = runnable->Run(context).ToLocalChecked();

        modules::moduleCache[moduleName].Reset(isolate, exports);
        args.GetReturnValue().Set(exports);
    }

    moduleDirectory = prevDirectory;
}