
#pragma once

#include "RasterCore.h"
#include "V8_Object.h"

#include "Window.h"

namespace raster
{
	class CL_Device : public V8_Object<CL_Device> {
		static v8::Persistent<v8::Function> constructor;
		cl::Device device;
	public:
		CL_Device();
		~CL_Device();


		static v8::Handle<v8::Object> newInstance();
		static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
		static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);
		static void getInfo(const v8::FunctionCallbackInfo<v8::Value>& info);

		void setDevice(cl::Device device);

		cl::Device& getDevice()
		{
			return device;
		}
	};

}