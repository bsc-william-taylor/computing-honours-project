
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