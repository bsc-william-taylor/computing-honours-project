
#include "Device.h"
#include "Context.h"

using namespace raster;


v8::Persistent<v8::ObjectTemplate> CL_Context::objectTemplate;
v8::Persistent<v8::Function> CL_Context::constructor;

CL_Context::CL_Context(CL_Device * device)
	: context(device->getDevice())
{	
}

CL_Context::~CL_Context()
{
}

void CL_Context::newInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if(args.Length() == 1)
	{
        auto templateObject = newTemplate(objectTemplate);
		auto deviceWrapper = CL_Device::unwrap(args[0].As<v8::Object>());
		v8::HandleScope scope(args.GetIsolate());
		
		auto device = new CL_Context(deviceWrapper);
		device->wrap(templateObject);
		args.GetReturnValue().Set(templateObject);
	}
	else
	{
		args.GetReturnValue().SetUndefined();
	}
}

void CL_Context::create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    cpp->Set(v8::String::NewFromUtf8(isolate, "Context"), constructor.Get(isolate));

	//auto templateObject = newTemplate(newInstance, "CL_Context");

	//templateObject->PrototypeTemplate()->Set(V8_String("getInfo"), v8::FunctionTemplate::New(isolate, getInfo)->GetFunction());

	//makeConstructor(cpp, templateObject, constructor, "CL_Context");
}