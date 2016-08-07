#pragma once

#include "RasterCore.h"
#include "V8_Object.h"

namespace raster {
	void timeout(const v8::FunctionCallbackInfo<v8::Value>& args);
	void pause(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void setupTimeModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		object->Set(V8_String("timeout"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), timeout));
		object->Set(V8_String("pause"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), pause));
	}
}