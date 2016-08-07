
#pragma once

#include "RasterCore.h"
#include "V8_Object.h"


namespace raster
{
	class CL_Platform : public V8_Object<CL_Platform> {
		static v8::Persistent<v8::Function> constructor;
		cl::Platform platform;
	public:
		CL_Platform();
		~CL_Platform();

		static v8::Handle<v8::Object> newInstance();
		static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
		static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);

		static void getInfo(const v8::FunctionCallbackInfo<v8::Value>& args);
		static void getDevices(const v8::FunctionCallbackInfo<v8::Value>& args);


		void setPlatform(cl::Platform platform);
	};

}