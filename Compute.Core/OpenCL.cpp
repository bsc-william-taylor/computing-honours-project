
#include "OpenCL.h"
#include "JsExtensions.h"
#include "JsObject.h"

void getPlatforms(v8::FunctionArgs args)
{
    if (args.Length() == 3)
    {
        auto isolate = args.GetIsolate();
        auto arg1 = args[0].As<v8::Number>();
        auto arg2 = args[1].As<v8::Array>();
        auto arg3 = args[2].As<v8::Array>();

        cl_uint devices = arg1->Value();
        cl_uint count = 0;

        auto platformBuffer = new cl_platform_id[devices];
        auto platformOut = arg2->IsNull() ? nullptr : platformBuffer;
        auto countOut = arg3->IsNull() ? nullptr : &count;

        clGetPlatformIDs(devices, platformOut, countOut);

        if (platformOut != nullptr)
        {
            for (auto i = 0; i < devices; ++i)
            {
                arg2->Set(i, v8::WrapPointer(platformBuffer[i]));
            }
        }

        if (countOut != nullptr)
        {
            arg3->Set(v8::NewString("length"), v8::Number::New(isolate, count));
        }

        delete platformBuffer;
    }
}

void getPlatformInfo(v8::FunctionArgs args)
{
    if (args.Length() == 2)
    {
        const auto arg1 = args[0].As<v8::Object>();
        const auto arg2 = args[1].As<v8::Number>();
        const auto sz = 10240;

        auto platformID = cl_platform_id(arg1->GetAlignedPointerFromInternalField(0));
        auto enumInfo = int(arg2->Value());
        char buffer[sz];

        clGetPlatformInfo(platformID, enumInfo, sz, buffer, nullptr);
        arg1->Set(v8::NewString("info"), v8::NewString(buffer));
    }
}

void getDevices(v8::FunctionArgs args)
{
    if (args.Length() == 5)
    {
        const auto isolate = args.GetIsolate();
        const auto arg1 = args[0].As<v8::Object>();
        const auto arg2 = args[1].As<v8::Number>();
        const auto arg3 = args[2].As<v8::Number>();
        const auto arg4 = args[3].As<v8::Array>();
        const auto arg5 = args[4].As<v8::Array>();

        cl_device_type deviceType = arg2->Value();
        cl_uint deviceArraySize = arg3->Value();
        cl_uint totalDevices = 0;

        auto platformID = static_cast<cl_platform_id>(arg1->GetAlignedPointerFromInternalField(0));
        auto deviceArray = new cl_device_id[deviceArraySize];
        auto devicesOut = arg4->IsNull() ? nullptr : deviceArray;
        auto totalOut = arg5->IsNull() ? nullptr : &totalDevices;

        clGetDeviceIDs(platformID, deviceType, deviceArraySize, devicesOut, totalOut);

        if (!arg4->IsNull())
        {
            for (auto i = 0; i < deviceArraySize; ++i)
            {
                arg4->Set(i, v8::WrapPointer(deviceArray[i]));
            }
        }

        if (!arg5->IsNull())
        {
            arg5->Set(v8::NewString("length"), v8::Number::New(isolate, totalDevices));
        }

        delete deviceArray;
    }
}

void getDeviceInfo(v8::FunctionArgs args)
{
    if (args.Length() == 2)
    {
        const auto arg1 = args[0].As<v8::Object>();
        const auto arg2 = args[1].As<v8::Number>();
        const auto sz = 10240;

        auto deviceID = cl_device_id(arg1->GetAlignedPointerFromInternalField(0));
        auto infoEnum = int(arg2->Value());

        char buffer[sz];
        clGetDeviceInfo(deviceID, infoEnum, sz, buffer, nullptr);
        arg1->Set(v8::NewString("info"), v8::NewString(buffer));
    }
}

void releaseContext(v8::FunctionArgs args)
{
    if (args.Length())
    {
        auto arg1 = args[0].As<v8::Object>();
        auto ctx = cl_context(arg1->GetAlignedPointerFromInternalField(0));

        if (ctx != nullptr)
        {
            clReleaseContext(ctx);
        }
    }
}

void createContextFromType(v8::FunctionArgs args)
{
    if (args.Length() == 5)
    {
        auto arg1 = args[0].As<v8::Array>();
        auto arg2 = args[1].As<v8::Number>();
        //auto arg3 = args[2].As<v8::Object>();
        //auto arg4 = args[3].As<v8::Object>();
        //auto arg5 = args[4].As<v8::Object>();

        auto platformObject = arg1->Get(1).As<v8::Object>();

        const auto platformID = cl_context_properties(platformObject->GetAlignedPointerFromInternalField(0));
        const auto platformType = arg1->Get(0)->NumberValue();
        const auto platformIndex = arg1->Get(2)->NumberValue();

        cl_context_properties properties[] = { platformType, platformID, platformIndex };

        auto ctx = clCreateContextFromType(properties, arg2->Value(), nullptr, nullptr, nullptr);

        args.GetReturnValue().Set(v8::WrapPointer(ctx));
    }
}

void compute::registerOpenCL(v8::Exports exports)
{
    AttachFunction(exports, "getPlatformIDs", getPlatforms);
    AttachFunction(exports, "getPlatformInfo", getPlatformInfo);

    AttachFunction(exports, "getDeviceIDs", getDevices);
    AttachFunction(exports, "getDeviceInfo", getDeviceInfo);

    AttachFunction(exports, "createContextFromType", createContextFromType);
    AttachFunction(exports, "releaseContext", releaseContext);
}