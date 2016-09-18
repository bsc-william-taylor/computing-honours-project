
#include "OpenCL.h"

void getPlatforms(v8::FunctionArgs args)
{
    if(args.Length() == 3)
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

        if(platformOut != nullptr)
        {
            for(auto i = 0; i < devices; ++i)
            {
                arg2->Set(i, v8::WrapPointer(platformBuffer[i]));
            }
        }
       
        if(countOut != nullptr)
        {
            arg3->Set(v8::NewString("length"), v8::Number::New(isolate, count));
        }

        delete platformBuffer;
    }
}

std::string deviceEnumName(int enumValue)
{
    std::string name = "unknown";

    switch (enumValue)
    {
        case CL_PLATFORM_EXTENSIONS: name = "extensions"; break;
        case CL_PLATFORM_VERSION: name = "version"; break;
        case CL_PLATFORM_PROFILE: name = "profile"; break;
        case CL_PLATFORM_VENDOR: name = "vendor"; break;
        case CL_PLATFORM_NAME: name = "name"; break;

    default:
        break;
    }

    return name;
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
        arg1->Set(v8::NewString(deviceEnumName(enumInfo)), v8::NewString(buffer));
    }
}

void getDevices(v8::FunctionArgs args)
{
    if(args.Length() == 2)
    {
        
    }
}

void getDeviceInfo(v8::FunctionArgs args)
{
    
}

void raster::registerOpenCL(v8::Local<v8::Object>& object) 
{
    AttachFunction(object, "getPlatformIDs", getPlatforms);
    AttachFunction(object, "getPlatformInfo", getPlatformInfo);

    AttachFunction(object, "getDeviceIDs", getDevices);
    AttachFunction(object, "getDeviceInfo", getDeviceInfo);
}