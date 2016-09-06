
#include "Console.h"

void raster::console::printLine(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    const auto argLength = args.Length();

    for (auto i{0}; i < argLength; ++i)
    {
        v8::String::Utf8Value str(args[i]);
        std::cout << *str << std::endl;
    }
}

void raster::console::print(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    const auto argLength = args.Length();

	for (auto i{0}; i < argLength; ++i)
    {
		v8::String::Utf8Value str(args[i]);
		std::cout << *str;
	}
}

void raster::console::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string input;
	std::getline(std::cin, input);
    
    const auto isolate = v8::Isolate::GetCurrent();
    const auto value = v8::String::NewFromUtf8(isolate, input.c_str());

	args.GetReturnValue().Set(value);
}

void raster::registerConsole(v8::Local<v8::Object>& object) 
{
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(v8::String::NewFromUtf8(isolate, "printLine"), v8::Function::New(isolate, console::printLine));
    object->Set(v8::String::NewFromUtf8(isolate, "print"), v8::Function::New(isolate, console::print));
    object->Set(v8::String::NewFromUtf8(isolate, "read"), v8::Function::New(isolate, console::read));
}