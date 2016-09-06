#include "Buffer.h"

using namespace raster;

v8::Persistent<v8::ObjectTemplate> CL_Buffer::objectTemplate;
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
	auto deviceWrapper = CL_Context::unwrap(args[0].As<v8::Object>());
	auto memSetting = args[1].As<v8::Integer>()->Value();
	auto size = args[2].As<v8::Integer>()->Value();
    auto templateObject = newTemplate(objectTemplate);
    auto device = new CL_Buffer(deviceWrapper, memSetting, size);
    device->wrap(templateObject);
    args.GetReturnValue().Set(templateObject);	
}

void CL_Buffer::create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    cpp->Set(v8::String::NewFromUtf8(isolate, "Buffer"), constructor.Get(isolate));
}
