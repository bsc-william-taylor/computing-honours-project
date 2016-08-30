
#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster {
	void cpuCacheLineSize(const v8::FunctionCallbackInfo<v8::Value>& args);
	void cpuCount(const v8::FunctionCallbackInfo<v8::Value>& args);
	void systemRam(const v8::FunctionCallbackInfo<v8::Value>& args);
	void has3DNow(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasAVX(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasAVX2(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasAltiVec(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasMMX(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasRDTSC(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasSSE(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasSSE2(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasSSE3(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasSSE41(const v8::FunctionCallbackInfo<v8::Value>& args);
	void hasSSE42(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void setupSystemModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		object->Set(V8_String("cpuCacheLineSize"), v8::FunctionTemplate::New(isolate, cpuCacheLineSize));
		object->Set(V8_String("cpuCount"), v8::FunctionTemplate::New(isolate, cpuCount));
		object->Set(V8_String("systemRam"), v8::FunctionTemplate::New(isolate, systemRam));
		object->Set(V8_String("has3DNow"), v8::FunctionTemplate::New(isolate, has3DNow));
		object->Set(V8_String("hasAVX"), v8::FunctionTemplate::New(isolate, hasAVX));
		object->Set(V8_String("hasAVX2"), v8::FunctionTemplate::New(isolate, hasAVX2));
		object->Set(V8_String("hasAltiVec"), v8::FunctionTemplate::New(isolate, hasAltiVec));
		object->Set(V8_String("hasMMX"), v8::FunctionTemplate::New(isolate, hasMMX));
		object->Set(V8_String("hasRDTSC"), v8::FunctionTemplate::New(isolate, hasRDTSC));
		object->Set(V8_String("hasSSE"), v8::FunctionTemplate::New(isolate, hasSSE));
		object->Set(V8_String("hasSSE2"), v8::FunctionTemplate::New(isolate, hasSSE2));
		object->Set(V8_String("hasSSE3"), v8::FunctionTemplate::New(isolate, hasSSE3));
		object->Set(V8_String("hasSSE41"), v8::FunctionTemplate::New(isolate, hasSSE41));
		object->Set(V8_String("hasSSE42"), v8::FunctionTemplate::New(isolate, hasSSE42));
	}
}