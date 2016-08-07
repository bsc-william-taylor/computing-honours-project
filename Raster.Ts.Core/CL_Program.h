
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "CL_Device.h"

#include "CL_Context.h"

namespace raster
{
	class CL_Program : public JsObject<CL_Program> {
		static v8::Persistent<v8::Function> constructor;
		cl::Program program;
	public:
		CL_Program(CL_Context * device, std::string source);
		~CL_Program();

		cl::Program& getProgram()
		{
			return program;
		}

		static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
		static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);

		// Member functions
		static void build(const v8::FunctionCallbackInfo<v8::Value>& build);
	};

}