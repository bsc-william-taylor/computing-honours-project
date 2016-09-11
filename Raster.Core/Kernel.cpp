
#include "Kernel.h"
#include "Buffer.h"

using namespace raster;

v8::Persistent<v8::ObjectTemplate> CL_Kernel::objectTemplate;
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

        auto that = newTemplate(objectTemplate);
        auto device = new CL_Kernel(programWrapper, *source);

        that->Set(V8_String("setArg"), v8::Function::New(args.GetIsolate(), setArg));

        device->wrap(that);
        args.GetReturnValue().Set(that);
    }
    else
    {
        args.GetReturnValue().SetUndefined();
    }
}

void CL_Kernel::create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    cpp->Set(v8::String::NewFromUtf8(isolate, "Kernel"), constructor.Get(isolate));
}

// Member functions
void CL_Kernel::setArg(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto kernelWrapper = unwrap(args);

    if (args.Length() == 2)
    {
        auto buffer = CL_Buffer::unwrap(args[1].As<v8::Object>());
        auto index = args[0].As<v8::Integer>()->Value();

        kernelWrapper->kernel.setArg(index, buffer->getBuffer());
    }
}