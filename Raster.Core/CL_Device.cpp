
#include "CL_Device.h"

using namespace raster;

v8::Persistent<v8::Function> CL_Device::constructor;

CL_Device::CL_Device()
{
	
}

CL_Device::~CL_Device()
{
	
}


v8::Handle<v8::Object> CL_Device::newInstance()
{
	return constructor.Get(v8::Isolate::GetCurrent())->NewInstance();
}

void CL_Device::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	auto that = info.This();
	auto device = new CL_Device();
	device->wrap(that);
	info.GetReturnValue().Set(that);
}

void CL_Device::setDevice(cl::Device device)
{
	this->device = device;
}

void CL_Device::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{/*
	auto templateObject = newTemplate(newInstance, "CL_Device");

	templateObject->PrototypeTemplate()->Set(V8_String("getInfo"), v8::FunctionTemplate::New(isolate, getInfo)->GetFunction());

	makeConstructor(cpp, templateObject, constructor, "CL_Device");*/
}

void CL_Device::getInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if(args.Length() == 1)
	{
		auto deviceWrapper = unwrap(args.This());
		auto type = args[0].As<v8::Integer>()->Value();
		auto device = deviceWrapper->device;

		cl::STRING_CLASS info;

		switch(type)
		{
			case 0: info = deviceWrapper->device.getInfo<CL_DEVICE_NAME>(); break;
			
			default: 
				break;
		}

		args.GetReturnValue().Set(V8_String(info.c_str()));
	}
}