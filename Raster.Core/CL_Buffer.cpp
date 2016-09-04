#include "CL_Buffer.h"

using namespace raster;

v8::Persistent<v8::Function> CL_Buffer::constructor;

CL_Buffer::CL_Buffer(CL_Context * context, int memSetting, int size)
	: buffer(context->getContext(), CL_MEM_READ_WRITE, size), size(size)
{
}

CL_Buffer::~CL_Buffer()
{
	
}

void CL_Buffer::newInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());

	auto deviceWrapper = CL_Context::unwrap(args[0].As<v8::Object>());
	auto memSetting = args[1].As<v8::Integer>()->Value();
	auto size = args[2].As<v8::Integer>()->Value();
	auto that = args.This();
	auto device = new CL_Buffer(deviceWrapper, memSetting, size);
	device->wrap(that);
	args.GetReturnValue().Set(that);
}

void CL_Buffer::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	//auto templateObject = newTemplate(newInstance, "CL_Buffer");

	//templateObject->PrototypeTemplate()->Set(V8_String("getInfo"), v8::FunctionTemplate::New(isolate, getInfo)->GetFunction());

	//makeConstructor(cpp, templateObject, constructor, "CL_Buffer");
}
