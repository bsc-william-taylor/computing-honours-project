
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Context.h"
#include "Device.h"

namespace raster
{
	class CL_CommandQueue : public JsObject<CL_CommandQueue> {
        static v8::Persistent<v8::ObjectTemplate> objectTemplate;
		static v8::Persistent<v8::Function> constructor;
		cl::CommandQueue queue;
	public:
		CL_CommandQueue(CL_Context * device, CL_Device *);
		~CL_CommandQueue();

		static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
		static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);

		// Member functions
		static void enqueueWriteBuffer(const v8::FunctionCallbackInfo<v8::Value>& build);
		static void enqueueNDRangeKernel(const v8::FunctionCallbackInfo<v8::Value>& build);
		static void enqueueReadBuffer(const v8::FunctionCallbackInfo<v8::Value>& build);
		static void finish(const v8::FunctionCallbackInfo<v8::Value>& build);
	};

}