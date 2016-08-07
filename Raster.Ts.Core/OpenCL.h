
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "CL_Platform.h"
#include "CL_Device.h"
#include "CL_Context.h"
#include "CL_Program.h"
#include "CL_Buffer.h"
#include "Kernel.h"
#include "CommandQueue.h"

namespace raster {
	void getPlatforms(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void setupOpenclModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		object->Set(V8_String("getPlatforms"), v8::FunctionTemplate::New(isolate, getPlatforms));

		CL_CommandQueue::create(object, isolate);
		CL_Kernel::create(object, isolate);
		CL_Buffer::create(object, isolate);
		CL_Program::create(object, isolate);
		CL_Context::create(object, isolate);
		CL_Platform::create(object, isolate);
		CL_Device::create(object, isolate);
	}
}
