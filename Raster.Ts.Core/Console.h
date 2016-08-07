
#pragma once

#include "RasterCore.h"

namespace raster {
	namespace console_module {
		void print(const v8::FunctionCallbackInfo<v8::Value>& args);
		void read(const v8::FunctionCallbackInfo<v8::Value>& args);
	}

	static void setupConsoleModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		object->Set(V8_String("print"), v8::FunctionTemplate::New(isolate, console_module::print));
		object->Set(V8_String("read"), v8::FunctionTemplate::New(isolate, console_module::read));
	}
}
