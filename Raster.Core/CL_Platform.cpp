
#include "CL_Platform.h"
#include "CL_Device.h"

using namespace raster;

v8::Persistent<v8::Function> CL_Platform::constructor;

CL_Platform::CL_Platform()
{
	
}

CL_Platform::~CL_Platform()
{
	
}

void CL_Platform::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	auto that = info.This();
	auto platform = new CL_Platform();
	platform->wrap(that);
	info.GetReturnValue().Set(that);
}

v8::Handle<v8::Object> CL_Platform::newInstance()
{
	return constructor.Get(v8::Isolate::GetCurrent())->NewInstance();
}

void CL_Platform::setPlatform(cl::Platform platform)
{
	this->platform = platform;
}

void CL_Platform::getInfo(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	if(info.Length() == 1)
	{
		auto infoID = info[0].As<v8::Integer>()->Value();
		auto platform = unwrap(info);
		cl::STRING_CLASS platformInfo("");

		switch(infoID)
		{
			case 0: platformInfo = platform->platform.getInfo<CL_PLATFORM_NAME>(); break;
			case 1: platformInfo = platform->platform.getInfo<CL_PLATFORM_VERSION>(); break;
			default: 
				break;
		}


		info.GetReturnValue().Set(V8_String(platformInfo.c_str()));
	}
	
}

void CL_Platform::getDevices(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto platformInstance = unwrap(args.This());
	std::vector<cl::Device> devices;
	platformInstance->platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	auto deviceArray = v8::Array::New(v8::Isolate::GetCurrent(), devices.size());
	
	for (auto i = 0; i < devices.size(); ++i) {
		auto deviceWrapper = CL_Device::newInstance();
		auto device = CL_Device::unwrap(deviceWrapper);
		device->setDevice(devices[i]);
		deviceArray->Set(i, deviceWrapper);
	}

	args.GetReturnValue().Set(deviceArray);
}

void CL_Platform::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{/*
	auto templateObject = newTemplate(newInstance, "CL_Platform");
	
	templateObject->PrototypeTemplate()->Set(V8_String("getDevices"), v8::FunctionTemplate::New(isolate, getDevices)->GetFunction());
	templateObject->PrototypeTemplate()->Set(V8_String("getInfo"), v8::FunctionTemplate::New(isolate, getInfo)->GetFunction());

	makeConstructor(cpp, templateObject, constructor, "CL_Platform");*/
}