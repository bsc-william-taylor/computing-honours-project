#pragma once

#include "RasterCore.h"
#include "V8_Object.h"

class TextFile : public V8_Object<TextFile>
{
	static v8::Persistent<v8::Function> constructor;
	std::string filename;
	std::string contents;
	std::string path;
	std::string ext;
public:
	TextFile();
	~TextFile();

	static void setContents(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getContents(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setFilename(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getFilename(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setPath(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getPath(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setExt(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getExt(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);

	static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);
	static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void read(const v8::FunctionCallbackInfo<v8::Value>& args);
};
