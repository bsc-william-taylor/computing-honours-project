#include "CommandQueue.h"
#include "Buffer.h"
#include "Kernel.h"

using namespace raster;

v8::Persistent<v8::ObjectTemplate> CL_CommandQueue::objectTemplate;
v8::Persistent<v8::Function> CL_CommandQueue::constructor;

CL_CommandQueue::CL_CommandQueue(CL_Context * context, CL_Device * device)
    : queue(context->getContext(), device->getDevice())
{

}

CL_CommandQueue::~CL_CommandQueue()
{
}

void CL_CommandQueue::newInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 2)
    {
        auto context = CL_Context::unwrap(args[0].As<v8::Object>());
        auto device = CL_Device::unwrap(args[1].As<v8::Object>());
        auto object = newTemplate(objectTemplate);

        object->Set(V8_String("enqueueWriteBuffer"), V8_Function(enqueueWriteBuffer));
        object->Set(V8_String("enqueueNDRangeKernel"), V8_Function(enqueueNDRangeKernel));
        object->Set(V8_String("enqueueReadBuffer"), V8_Function(enqueueReadBuffer));
        object->Set(V8_String("finish"), V8_Function(finish));

        auto queue = new CL_CommandQueue(context, device);
        queue->wrap(object);
        args.GetReturnValue().Set(object);
    }
    else
    {
        args.GetReturnValue().SetUndefined();
    }
}

void CL_CommandQueue::create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    cpp->Set(v8::String::NewFromUtf8(isolate, "CommandQueue"), constructor.Get(isolate));
    /*
        auto templateObject = newTemplate(newInstance, "CL_CommandQueue");
        auto proto = templateObject->PrototypeTemplate();


        makeConstructor(cpp, templateObject, constructor, "CL_CommandQueue");*/
}

void CL_CommandQueue::enqueueWriteBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto commandQueue = unwrap(args);

    auto bufferWrapper = CL_Buffer::unwrap(args[0].As<v8::Object>());
    auto block = args[1].As<v8::Boolean>()->Value();
    auto offset = args[2].As<v8::Number>()->Value();
    auto size = args[3].As<v8::Number>()->Value();
    auto data = args[4].As<v8::Array>();

    std::vector<int> arr(data->Length());
    for (auto i = 0; i < data->Length(); i++) {
        arr[i] = data->Get(i).As<v8::Integer>()->Value();
    }

    commandQueue->queue.enqueueWriteBuffer(bufferWrapper->getBuffer(), block, offset, size, arr.data());
}

void CL_CommandQueue::enqueueNDRangeKernel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto commandQueue = unwrap(args);
    auto kernelWrapper = CL_Kernel::unwrap(args[0].As<v8::Object>());
    auto kernel = kernelWrapper->getKernel();
    //auto dimension = args[1].As<v8::Integer>()->Value();
    auto range = args[2].As<v8::Integer>()->Value();
    //auto local = args[3].As<v8::Integer>()->Value();

    commandQueue->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(range), cl::NullRange);
}

void CL_CommandQueue::enqueueReadBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto commandQueue = unwrap(args);

    auto bufferWrapper = CL_Buffer::unwrap(args[0].As<v8::Object>());
    auto buffer = bufferWrapper->getBuffer();
    auto block = args[1].As<v8::Boolean>()->Value();
    auto offset = args[2].As<v8::Number>()->Value();
    auto size = args[3].As<v8::Number>()->Value();
    auto data = args[4].As<v8::Array>();

    auto sz = size / sizeof(int);
    auto output = new int[sz];
    commandQueue->queue.enqueueReadBuffer(bufferWrapper->getBuffer(), block, offset, size, output);
    data->Set(V8_String("length"), V8_Integer(sz));
    for (auto i = 0; i < sz; i++) {
        data->Set(i, V8_Integer(output[i]));
    }

    delete output;
}

void CL_CommandQueue::finish(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto commandQueue = unwrap(args);
    commandQueue->queue.finish();
}