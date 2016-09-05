
#include "Modules.h"
#include "System.h"
#include "DateTime.h"
#include "Console.h"
#include "Window.h"
#include "OpenGL.h"
#include "OpenCL.h"
#include "Fs.h"

std::string readScript(const std::string& filename)
{
    std::ifstream file(filename);
    std::string data;

    if (file.is_open())
    {
        std::string temp;
        while (getline(file, temp))
        {
            data += temp + "\n";
        }

        file.close();
    }

    return data;
}

std::string parseInternalModulePath(std::string name)
{
    auto path = Poco::Path(cwd);
    path.append("/modules/");
    path.append(name);
    path.setExtension("js");
    return path.toString();
}

std::string parseExternalModulePath(std::string name)
{
    auto path = Poco::Path(Poco::Path::current());
    path.append(name);
    path.setExtension("js");
    return path.toString();
}

std::map<std::string, raster::JsModule> raster::modules::moduleCache = {};

std::map<std::string, raster::JsModuleRegisterCallback> raster::modules::moduleBindings = 
{{
    { "datetime", [](v8::Local<v8::Object>& object) { raster::registerDateTime(object); } },
    { "display", []( v8::Local<v8::Object>& object) { raster::registerDisplay(object); } },
    { "console", [](v8::Local<v8::Object>& object) { raster::registerConsole(object); } },
    { "system", [](v8::Local<v8::Object>& object) { raster::registerSystem(object); } },
    { "opencl", [](v8::Local<v8::Object>& object) { raster::registerOpenCL(object); } },
    { "opengl", [](v8::Local<v8::Object>& object) { raster::registerOpenGL(object); } },
    { "fs", [](v8::Local<v8::Object>& object) { raster::registerFs(object); } }
}};

v8::Local<v8::ObjectTemplate> raster::registerCommonJsModules()
{
    auto isolate = v8::Isolate::GetCurrent();
	auto moduleTemplate = v8::ObjectTemplate::New(isolate);

	moduleTemplate->Set(V8_String("require"), v8::FunctionTemplate::New(isolate, require));
	moduleTemplate->Set(V8_String("exports"), v8::ObjectTemplate::New(isolate));
    moduleTemplate->Set(V8_String("cpp"), v8::ObjectTemplate::New(isolate));

	return moduleTemplate;
}

void raster::clearCommonJsModules()
{
	modules::moduleCache.clear();
}

raster::ModuleType moduleType(const std::string& path)
{
    if (path.find(".") != std::string::npos || path.find("/") != std::string::npos)
    {
        return raster::ModuleType::External;
    }

    return raster::ModuleType::Internal;
}

v8::Local<v8::String> createScript(v8::Isolate * isolate, v8::String::Utf8Value& module)
{
	std::string filename;

	if(moduleType(*module) == raster::ModuleType::Internal)
	{
		filename = parseInternalModulePath(*module);
	}
	else
	{
		filename = parseExternalModulePath(*module);
	}

	auto script = readScript(filename.c_str());
	script.insert(0, "(function(raster){");
	script.append("})(cpp);");

	return v8::String::NewFromUtf8(isolate, script.c_str(), v8::NewStringType::kNormal).ToLocalChecked();
}

void raster::require(const v8::FunctionCallbackInfo<v8::Value>& args) {
	if (args.Length() == 0) {
		args.GetReturnValue().SetUndefined();
		return;
	}

	auto isolate = args.GetIsolate();
	auto context = isolate->GetCurrentContext();
	auto global = context->Global();

	v8::String::Utf8Value moduleName(args[0]);

	if(modules::moduleCache.find(*moduleName) != modules::moduleCache.end())
	{
		args.GetReturnValue().Set(modules::moduleCache[*moduleName].Get(isolate));
	}
	else
	{
		auto currentExports = global->Get(v8::String::NewFromUtf8(isolate, "exports"));
		auto currentCpp = global->Get(v8::String::NewFromUtf8(isolate, "cpp"));
		auto exports = v8::ObjectTemplate::New()->NewInstance();
		auto module = v8::ObjectTemplate::New()->NewInstance();
		auto raster = v8::Object::New(isolate);

		auto script = createScript(isolate, moduleName);
		
		if (modules::moduleBindings.find(*moduleName) != modules::moduleBindings.end())
        {
			modules::moduleBindings[*moduleName](raster);
        }

		module->Set(v8::String::NewFromUtf8(isolate, "exports"), exports);
        module->Set(v8::String::NewFromUtf8(isolate, "name"), v8::String::NewFromUtf8(isolate, *moduleName));
		global->Set(v8::String::NewFromUtf8(isolate, "cpp"), raster);
		global->Set(v8::String::NewFromUtf8(isolate, "module"), module);
		global->Set(v8::String::NewFromUtf8(isolate, "exports"), exports);

		v8::Script::Compile(context, script).ToLocalChecked()->Run(context);

		global->Set(v8::String::NewFromUtf8(isolate, "exports"), currentExports);
		global->Set(v8::String::NewFromUtf8(isolate, "cpp"), currentCpp);

		args.GetReturnValue().Set(exports);

		modules::moduleCache[*moduleName].Reset(v8::Isolate::GetCurrent(), exports);
	}
}