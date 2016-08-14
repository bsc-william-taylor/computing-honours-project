
#include "Modules.h"


v8::Local<v8::ObjectTemplate> raster::setupModuleSystem()
{
	auto moduleTemplate = v8::ObjectTemplate::New();
	auto isolate = v8::Isolate::GetCurrent();

	moduleTemplate->Set(V8_String("require"), v8::FunctionTemplate::New(isolate, require));
	moduleTemplate->Set(V8_String("exports"), v8::ObjectTemplate::New(isolate));

	return moduleTemplate;
}

void raster::clear()
{
	modules::moduleCache.clear();
}

std::string getScript(const char * filename)
{
	std::ifstream file(filename);
	std::string data;
	
	if (file.is_open()) {
		std::string temp;
		while (getline(file, temp)) {
			data += temp + "\n";
		}

		file.close();
	}

	return data;
}

std::string getInternalModuleFilename(std::string name)
{
	auto path = Poco::Path(cwd);
	path.append("/modules/");
	path.append(name);
	path.setExtension("js");
	return path.toString();
}

std::string getExternalModuleFilename(std::string name)
{
	auto path = Poco::Path(cwd);
	path.append("/compiler/output/");
	path.append(name);
	path.setExtension("js");
	return path.toString();
}

v8::Local<v8::String> createScript(v8::Isolate * isolate, v8::String::Utf8Value& module)
{
	auto type = raster::determineModuleType(*module);
	std::string filename {""};
	std::string script {""};

	if(type == raster::ModuleType::Internal)
	{
		filename = getInternalModuleFilename(*module);
	}
	else
	{
		filename = getExternalModuleFilename(*module);
	}

	script = getScript(filename.c_str());
	script.insert(0, "(function(){");
	script.append("})();");

	return v8::String::NewFromUtf8(isolate, script.c_str(), v8::NewStringType::kNormal).ToLocalChecked();
}

raster::ModuleType raster::determineModuleType(const std::string& path)
{
	if(path.find(".") != std::string::npos || path.find("/") != std::string::npos)
	{
		return ModuleType::External;
	}
	
	return ModuleType::Internal;
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
		auto cpp = v8::ObjectTemplate::New();

		auto script = createScript(isolate, moduleName);
		
		if (modules::moduleBindings.find(*moduleName) != modules::moduleBindings.end())
        {
			modules::moduleBindings[*moduleName](isolate, cpp);
        }

		module->Set(v8::String::NewFromUtf8(isolate, "exports"), exports);

		global->Set(v8::String::NewFromUtf8(isolate, "cpp"), cpp->NewInstance());
		global->Set(v8::String::NewFromUtf8(isolate, "module"), module);
		global->Set(v8::String::NewFromUtf8(isolate, "exports"), exports);

		v8::Script::Compile(context, script).ToLocalChecked()->Run(context);

		global->Set(v8::String::NewFromUtf8(isolate, "exports"), currentExports);
		global->Set(v8::String::NewFromUtf8(isolate, "cpp"), currentCpp);

		args.GetReturnValue().Set(exports);

		modules::moduleCache[*moduleName].Reset(v8::Isolate::GetCurrent(), exports);
	}
}