
#pragma once

#include "TimeModule.h"
#include "Computer.h"
#include "RasterCore.h"
#include "Console.h"
#include "Renderer.h"
#include "Console.h"
#include "Window.h"
#include "Fs.h"
#include "OpenGL.h"
#include "OpenCL.h"

namespace raster {
	enum class ModuleType { Internal, External };

	namespace modules {
		static std::map<std::string, v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>>> moduleCache;
		static std::map<std::string, std::function<void(v8::Isolate *, v8::Local<v8::ObjectTemplate>&)>> moduleBindings = {{
			{ "computer", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupComputerModule(isolate, object); } },
			{ "graphics", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupGraphicsModule(isolate, object); } },
			{ "display", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupDisplayModule(isolate, object); } },
			{ "console", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupConsoleModule(isolate, object); } },
			{ "opencl", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupOpenclModule(isolate, object); } },
			{ "opengl", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupOpenglModule(isolate, object); } },
			{ "time", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupTimeModule(isolate, object); } },
			{ "fs", [](v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>&object) { setupFsModule(isolate, object); } }
		}};
	}

	v8::Local<v8::ObjectTemplate> setupModuleSystem();

	void require(const v8::FunctionCallbackInfo<v8::Value>& args);
    void merge(const v8::FunctionCallbackInfo<v8::Value>& args);
	void clear();

	ModuleType determineModuleType(const std::string&);
}
