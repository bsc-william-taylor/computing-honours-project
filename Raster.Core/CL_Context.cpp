
#include "CL_Device.h"
#include "CL_Context.h"

using namespace raster;

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
		auto deviceWrapper = CL_Device::unwrap(args[0].As<v8::Object>());
		v8::HandleScope scope(args.GetIsolate());
		auto that = args.This();
		auto device = new CL_Context(deviceWrapper);
		device->wrap(that);
		args.GetReturnValue().Set(that);
	}
	else
	{
		args.GetReturnValue().SetUndefined();
	}
}

void CL_Context::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	//auto templateObject = newTemplate(newInstance, "CL_Context");

	//templateObject->PrototypeTemplate()->Set(V8_String("getInfo"), v8::FunctionTemplate::New(isolate, getInfo)->GetFunction());

	//makeConstructor(cpp, templateObject, constructor, "CL_Context");
}