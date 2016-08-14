
#include "Console.h"

void raster::console_module::print(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	for (auto i = 0; i < args.Length(); i++) {
		v8::String::Utf8Value str(args[i]);
		std::cout << *str << std::endl;
	}
}

void raster::console_module::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string input;
	std::getline(std::cin, input);
	args.GetReturnValue().Set(V8_String(input.c_str()));
}