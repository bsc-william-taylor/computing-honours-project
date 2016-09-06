#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster {
	void perspective(const v8::FunctionCallbackInfo<v8::Value>& args);
	void loadIdentity(const v8::FunctionCallbackInfo<v8::Value>& args);
	void matrixMode(const v8::FunctionCallbackInfo<v8::Value>& args);
	void translate(const v8::FunctionCallbackInfo<v8::Value>& args);
	void rotate(const v8::FunctionCallbackInfo<v8::Value>& args);

	void clearColor(const v8::FunctionCallbackInfo<v8::Value>& args);
	void vertex2f(const v8::FunctionCallbackInfo<v8::Value>& args);
	void vertex3f(const v8::FunctionCallbackInfo<v8::Value>& args);
	void color3f(const v8::FunctionCallbackInfo<v8::Value>& args);
	void clear(const v8::FunctionCallbackInfo<v8::Value>& args);
	void enable(const v8::FunctionCallbackInfo<v8::Value>& args);
	void begin(const v8::FunctionCallbackInfo<v8::Value>& args);
	void end(const v8::FunctionCallbackInfo<v8::Value>& args);


	void registerOpenGL(v8::Local<v8::Object>& object);
}