
#include "OpenCL.h"

void raster::getPlatforms(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platformArray = v8::Array::New(v8::Isolate::GetCurrent(), platforms.size());

	for (auto i = 0; i < platforms.size(); i++)
	{
		auto platformWrapper = CL_Platform::newInstance();
		auto pointer = CL_Platform::unwrap(platformWrapper);
		pointer->setPlatform(platforms[i]);
		platformArray->Set(i, platformWrapper);
	}
	
	args.GetReturnValue().Set(platformArray);
}

void raster::registerOpenCL(v8::Local<v8::Object>& object) {
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(V8_String("getPlatforms"), v8::Function::New(isolate, getPlatforms));

    CL_CommandQueue::create(object, isolate);
    CL_Platform::create(object, isolate);
    CL_Program::create(object, isolate);
    CL_Context::create(object, isolate);
    CL_Kernel::create(object, isolate);
    CL_Buffer::create(object, isolate);
    CL_Device::create(object, isolate);
}