
#include "OpenCL.h"
#include "JsExtensions.h"
#include "JsObject.h"

void getPlatforms(v8::FunctionArgs args)
{
    auto paltformDetails = GetArray(args[2]);
    auto platformList = GetArray(args[1]);
    
    cl_uint devices = GetNumber(args[0]);
    cl_uint count = 0;

    auto platformBuffer = std::unique_ptr<cl_platform_id[]>(new cl_platform_id[devices]);
    auto platformOut = platformList->IsNull() ? nullptr : platformBuffer.get();
    auto countOut = paltformDetails->IsNull() ? nullptr : &count;
    auto error = clGetPlatformIDs(devices, platformOut, countOut);

    if (platformOut != nullptr)
    {
        for (auto i = 0; i < devices; ++i)
        {
            platformList->Set(i, v8::WrapPointer(platformBuffer[i]));
        }
    }

    if (countOut != nullptr)
    {
        paltformDetails->Set(v8::NewString("length"), v8::NewNumber(count));
    }

    Return(args, error);
}

void getPlatformInfo(v8::FunctionArgs args)
{
    char buffer[16384];

    const auto platform = GetObject(args[0]);
    const auto platformID = static_cast<cl_platform_id>(UnwrapPointer(args[0]));
    const auto flags = GetNumber(args[1]);
    const auto error = clGetPlatformInfo(platformID, flags, 16384, buffer, nullptr);

    platform->Set(v8::NewString("info"), v8::NewString(buffer));

    Return(args, error);
}

void getDevices(v8::FunctionArgs args)
{
    cl_device_type deviceType = GetNumber(args[1]);
    cl_uint deviceArraySize = GetNumber(args[2]);
    cl_uint totalDevices = 0;

    const auto deviceList = GetArray(args[3]);
    const auto deviceDetails = GetArray(args[4]);

    auto deviceArray = std::unique_ptr<cl_device_id[]>(new cl_device_id[deviceArraySize]);
    auto platformID = static_cast<cl_platform_id>(UnwrapPointer(args[0]));
    auto devicesOut = deviceList->IsNull() ? nullptr : deviceArray.get();
    auto totalOut = deviceDetails->IsNull() ? nullptr : &totalDevices;
    auto error = clGetDeviceIDs(platformID, deviceType, deviceArraySize, devicesOut, totalOut);

    if (!deviceList->IsNull())
    {
        for (auto i = 0; i < deviceArraySize; ++i)
        {
            deviceList->Set(i, v8::WrapPointer(deviceArray[i]));
        }
    }

    if (!deviceDetails->IsNull())
    {
        deviceDetails->Set(v8::NewString("length"), v8::NewNumber(totalDevices));
    }
    
    Return(args, error);
}

void getDeviceInfo(v8::FunctionArgs args)
{
    char buffer[16384];

    const auto deviceID = static_cast<cl_device_id>(UnwrapPointer(args[0]));
    const auto device = GetObject(args[0]);
    const auto param = GetNumber(args[1]); 
    const auto error = clGetDeviceInfo(deviceID, param, 16384, buffer, nullptr);
        
    device->Set(v8::NewString("info"), v8::NewString(buffer));

    Return(args, error);
}

using cl_prop = cl_context_properties;

void createContextFromType(v8::FunctionArgs args)
{
    if (args.Length() == 5)
    {
        auto array = GetArray(args[0]);
        auto flags = GetNumber(args[1]);
   
        const auto platformID = cl_context_properties(UnwrapPointer(array->Get(1)));
        const auto platformType = array->Get(0)->NumberValue();
        const auto platformIndex = array->Get(2)->NumberValue();

        cl_context_properties properties[] = { (cl_prop)platformType, (cl_prop)platformID, (cl_prop)platformIndex };
        cl_context context = clCreateContextFromType(properties, flags, nullptr, nullptr, nullptr);
        
        Return(args, v8::WrapPointer(context));
    }
}

void createCommandQueue(v8::FunctionArgs args)
{
    auto context = static_cast<cl_context>(UnwrapPointer(args[0]));
    auto deviceID = static_cast<cl_device_id>(UnwrapPointer(args[1]));
    auto commandQueue = clCreateCommandQueue(context, deviceID, 0, nullptr);

    Return(args, v8::WrapPointer(commandQueue));
}

void createProgramWithSource(v8::FunctionArgs args)
{   
    auto context = static_cast<cl_context>(UnwrapPointer(args[0]));
    auto count = GetNumber(args[1]);
    auto text = GetString(args[2]);

    auto sources = std::unique_ptr<char const *[]>(new char const *[1]{ text.c_str() });
    auto program = clCreateProgramWithSource(context, count, sources.get(), nullptr, nullptr);

    Return(args, v8::WrapPointer(program));
}

void buildProgram(v8::FunctionArgs args)
{
    auto program = static_cast<cl_program>(UnwrapPointer(args[0]));
    auto error =  clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
    
    Return(args, error);
}

void getProgramBuildInfo(v8::FunctionArgs args)
{
    char buildLog[16384];

    auto deviceID = static_cast<cl_device_id>(UnwrapPointer(args[1]));
    auto program = static_cast<cl_program>(UnwrapPointer(args[0]));
    auto params = GetNumber(args[2]);
    auto object = GetObject(args[4]);

    auto error = clGetProgramBuildInfo(program, deviceID, params, sizeof(buildLog), buildLog, nullptr);
    object->Set(v8::NewString("log"), v8::NewString(buildLog));
    Return(args, error);
}

void createKernel(v8::FunctionArgs args)
{
    auto program = static_cast<cl_program>(UnwrapPointer(args[0]));
    auto name = GetString(args[1]);
    auto kernel = clCreateKernel(program, GetString(args[1]).c_str(), nullptr);

    Return(args, v8::WrapPointer(kernel));
}

void releaseCommandQueue(v8::FunctionArgs args)
{
    Return(args, clReleaseCommandQueue(cl_command_queue(UnwrapPointer(args[0]))));
}

void releaseProgram(v8::FunctionArgs args)
{
    Return(args, clReleaseProgram(cl_program(UnwrapPointer(args[0]))));
}

void releaseMemObject(v8::FunctionArgs args)
{
    Return(args, clReleaseMemObject(cl_mem(UnwrapPointer(args[0]))));
}

void releasekernel(v8::FunctionArgs args)
{
    Return(args, clReleaseKernel(cl_kernel(UnwrapPointer(args[0]))));
}

void releaseContext(v8::FunctionArgs args)
{
    Return(args, clReleaseContext(cl_context(v8::UnwrapPointer(args[0]))));
}

void enqueueNDRangeKernel(v8::FunctionArgs args)
{
    auto commandQueue = static_cast<cl_command_queue>(UnwrapPointer(args[0]));
    auto kernel = static_cast<cl_kernel>(UnwrapPointer(args[1]));
    auto index = GetNumber(args[2]);

    auto globalWorkArray = GetTypedArray(args[4]);
    auto localWorkArray = GetTypedArray(args[5]);
    auto gwsPointer = globalWorkArray->IsNull() ? nullptr : globalWorkArray->Buffer()->GetContents().Data();
    auto lwsPointer = localWorkArray->IsNull() ? nullptr : localWorkArray->Buffer()->GetContents().Data();
    auto error = clEnqueueNDRangeKernel(commandQueue, kernel, index, nullptr, (size_t*)gwsPointer, (size_t*)lwsPointer, 0, nullptr, nullptr);

    Return(args, error);
}

void enqueueReadBuffer(v8::FunctionArgs args)
{
    auto commandQueue = static_cast<cl_command_queue>(UnwrapPointer(args[0]));
    auto memory = static_cast<cl_mem>(UnwrapPointer(args[1]));
    auto array = GetTypedArray(args[5]);
    auto flag = GetNumber(args[2]);
    auto len = GetNumber(args[4]);
 
    auto pointer = array->IsNull() ? nullptr : array->Buffer()->GetContents().Data();
    auto error = clEnqueueReadBuffer(commandQueue, memory, flag, 0, len, pointer, 0, nullptr, nullptr);

    Return(args, error);
}

void createBuffer(v8::FunctionArgs args)
{
    auto context = static_cast<cl_context>(UnwrapPointer(args[0]));
    auto array = GetTypedArray(args[3]);
    auto flags = GetNumber(args[1]);
    auto size = GetNumber(args[2]);

    auto pointer = array->IsNull() ? nullptr : array->Buffer()->GetContents().Data();
    auto buffer = clCreateBuffer(context, flags, size, pointer, nullptr);
    Return(args, v8::WrapPointer(buffer));
}

void setKernelArg(v8::FunctionArgs args)
{
    auto kernel = cl_kernel(UnwrapPointer(args[0]));
    auto index = GetNumber(args[1]);
    auto size = GetNumber(args[2]);

    // Convert to typed arrays
    if(args[3]->IsObject())
    {
        auto buffer = UnwrapPointer(args[3]);
        Return(args, clSetKernelArg(kernel, index, sizeof(cl_mem), &buffer));
    }
    else if(args[3]->IsNumber())
    {
        auto number = static_cast<int>(GetNumber(args[3]));
        Return(args, clSetKernelArg(kernel, index, sizeof(cl_int), &number));
    }
    else if (args[3]->IsString())
    {
        auto string = GetString(args[3]);
        Return(args, clSetKernelArg(kernel, index, size, string.c_str()));
    }
}

void createImage2D(v8::FunctionArgs args)
{
    auto context = cl_context(UnwrapPointer(args[0]));
    auto flags = GetNumber(args[1]);
    auto format = GetObject(args[2]);
    auto width = GetNumber(args[3]);
    auto height = GetNumber(args[4]);
    auto data = UnwrapPointer(args[6]);
    
    cl_image_format clFormat;
    clFormat.image_channel_data_type = GetNumber(format->Get(v8::NewString("image_channel_data_type")));
    clFormat.image_channel_order = GetNumber(format->Get(v8::NewString("image_channel_order")));

    auto err = 0;
    auto image = clCreateImage2D(context, flags, &clFormat, width, height, 0, data, &err);
    args.GetReturnValue().Set(v8::WrapPointer(image));
}

void createSampler(v8::FunctionArgs args)
{
    auto context = cl_context(UnwrapPointer(args[0]));
    auto normalise = GetNumber(args[1]);
    auto param1 = GetNumber(args[2]);
    auto param2 = GetNumber(args[3]);
    auto error = 0;
    auto sampler = clCreateSampler(context, normalise, param1, param2, &error);
    args.GetReturnValue().Set(v8::WrapPointer(sampler));
}

void enqueueReadImage(v8::FunctionArgs args)
{
    auto commandQueue = cl_command_queue(UnwrapPointer(args[0]));
    auto output = cl_mem(UnwrapPointer(args[1]));
    auto boolean = GetNumber(args[2]);
    auto origin = args[3].As<v8::TypedArray>();
    auto region = args[4].As<v8::TypedArray>();
    auto buffer = args[7].As<v8::ArrayBuffer>();

    auto originPtr = (const size_t *)origin->Buffer()->GetContents().Data();
    auto regionPtr = (const size_t *)region->Buffer()->GetContents().Data();
    auto bufferPtr = buffer->GetContents().Data();

    auto err = clEnqueueReadImage(commandQueue, output, boolean, originPtr, regionPtr, 0, 0, bufferPtr, 0, nullptr, nullptr);
}

void releaseSampler(v8::FunctionArgs args)
{
    clReleaseSampler(cl_sampler(UnwrapPointer(args[0])));
}

void hasImageSupport(v8::FunctionArgs args)
{
    auto device = cl_device_id(UnwrapPointer(args[0]));

    cl_bool imageSupport = CL_FALSE;
    clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(cl_bool), &imageSupport, nullptr);
    args.GetReturnValue().Set(imageSupport == CL_TRUE ? true : false);
}

void compute::registerOpenCL(v8::Exports exports)
{
    AttachFunction(exports, "getPlatformIDs", getPlatforms);
    AttachFunction(exports, "getPlatformInfo", getPlatformInfo);
    AttachFunction(exports, "getDeviceIDs", getDevices);
    AttachFunction(exports, "getDeviceInfo", getDeviceInfo);
    AttachFunction(exports, "createKernel", createKernel);
    AttachFunction(exports, "setKernelArg", setKernelArg);
    AttachFunction(exports, "createCommandQueue", createCommandQueue);
    AttachFunction(exports, "createProgramWithSource", createProgramWithSource);
    AttachFunction(exports, "getProgramBuildInfo", getProgramBuildInfo);
    AttachFunction(exports, "buildProgram", buildProgram);
    AttachFunction(exports, "createContextFromType", createContextFromType);
    AttachFunction(exports, "enqueueNDRangeKernel", enqueueNDRangeKernel);
    AttachFunction(exports, "enqueueReadBuffer", enqueueReadBuffer);
    AttachFunction(exports, "createBuffer", createBuffer);
    AttachFunction(exports, "releaseCommandQueue", releaseCommandQueue);
    AttachFunction(exports, "releaseProgram", releaseProgram);
    AttachFunction(exports, "releaseContext", releaseContext);
    AttachFunction(exports, "releaseKernel", releasekernel);
    AttachFunction(exports, "createImage2D", createImage2D);
    AttachFunction(exports, "createSampler", createSampler);
    AttachFunction(exports, "releaseSampler", releaseSampler);
    AttachFunction(exports, "enqueueReadImage", enqueueReadImage);
    AttachFunction(exports, "releaseMemObject", releaseMemObject);
    AttachFunction(exports, "hasImageSupport", hasImageSupport);
}