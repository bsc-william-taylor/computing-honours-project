
#include "Kernel.h"
#include "CL_Buffer.h"

using namespace raster;

v8::Persistent<v8::Function> CL_Kernel::constructor;

CL_Kernel::CL_Kernel(CL_Program * program, std::string kernelName)
	: kernel(program->getProgram(), kernelName.c_str())
{
}

CL_Kernel::~CL_Kernel()
{
	
}

void CL_Kernel::newInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() == 2)
	{
		auto programWrapper = CL_Program::unwrap(args[0].As<v8::Object>());
		v8::String::Utf8Value source(args[1]);

		v8::HandleScope scope(args.GetIsolate());
		auto that = args.This();
		auto device = new CL_Kernel(programWrapper, *source);
		device->wrap(that);
		args.GetReturnValue().Set(that);
	}
	else
	{
		args.GetReturnValue().SetUndefined();
	}
}

void CL_Kernel::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	auto templateObject = newTemplate(newInstance, "CL_Kernel");

	templateObject->PrototypeTemplate()->Set(V8_String("setArg"), v8::FunctionTemplate::New(isolate, setArg)->GetFunction());

	makeConstructor(cpp, templateObject, constructor, "CL_Kernel");
}

// Member functions
void CL_Kernel::setArg(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto kernelWrapper = unwrap(args);

	if(args.Length() == 2)
	{
		auto buffer = CL_Buffer::unwrap(args[1].As<v8::Object>());
		auto index = args[0].As<v8::Integer>()->Value();
		
		kernelWrapper->kernel.setArg(index, buffer->getBuffer());
	}
}