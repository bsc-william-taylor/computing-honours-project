#include "Program.h"

using namespace raster;

v8::Persistent<v8::ObjectTemplate> CL_Program::objectTemplate;
v8::Persistent<v8::Function> CL_Program::constructor;

CL_Program::CL_Program(CL_Context * device, std::string source)
	: program(cl::Program(device->getContext(), source))
{
}

CL_Program::~CL_Program()
{
}

void CL_Program::newInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() == 2)
	{
        auto isolate = v8::Isolate::GetCurrent();
		auto context = CL_Context::unwrap(args[0].As<v8::Object>());
        auto templateObject = newTemplate(objectTemplate);

        templateObject->Set(V8_String("build"), v8::Function::New(isolate, build));

		v8::String::Utf8Value source(args[1]);
		auto device = new CL_Program(context, *source);
		device->wrap(templateObject);
		args.GetReturnValue().Set(templateObject);
	}
	else
	{
		args.GetReturnValue().SetUndefined();
	}
}

void CL_Program::build(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if(args.Length() == 1)
	{
		auto programWrapper = unwrap(args);
		auto deviceWrapper = CL_Device::unwrap(args[0].As<v8::Object>());
		auto result = programWrapper->program.build({ deviceWrapper->getDevice() });

		if (result != 0)
		{
			std::cerr << programWrapper->program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(deviceWrapper->getDevice()) << std::endl;
		}

		args.GetReturnValue().Set(result);
	}
	else
	{
		args.GetReturnValue().Set(CL_BUILD_ERROR);
	}
}

void CL_Program::create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    cpp->Set(v8::String::NewFromUtf8(isolate, "Program"), constructor.Get(isolate));
}
