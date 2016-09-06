
#include "Device.h"

using namespace raster;


v8::Persistent<v8::ObjectTemplate> CL_Device::objectTemplate;
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
    auto that = newTemplate(objectTemplate);
	auto device = new CL_Device();

    that->Set(V8_String("getInfo"), v8::Function::New(info.GetIsolate(), getInfo));

	device->wrap(that);
	info.GetReturnValue().Set(that);
}

void CL_Device::setDevice(cl::Device device)
{
	this->device = device;
}

void CL_Device::create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    cpp->Set(v8::String::NewFromUtf8(isolate, "Device"), constructor.Get(isolate));
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