
#include "Console.h"
#include "JsExtensions.h"

void raster::console::printLine(v8::FunctionArgs args)
{
    const auto argLength = args.Length();

    for (auto i{ 0 }; i < argLength; ++i)
    {
        if (args[i]->IsString())
        {
            v8::String::Utf8Value str(args[i]);
            std::cout << *str << std::endl;
        }
    }
}

void raster::console::print(v8::FunctionArgs args)
{
    const auto argLength = args.Length();

    for (auto i{ 0 }; i < argLength; ++i)
    {
        if (args[i]->IsString())
        {
            v8::String::Utf8Value str(args[i]);
            std::cout << *str;
        }
    }
}

void raster::console::read(v8::FunctionArgs args)
{
    std::string input;
    std::getline(std::cin, input);

    const auto isolate = v8::Isolate::GetCurrent();
    const auto value = v8::String::NewFromUtf8(isolate, input.c_str());

    args.GetReturnValue().Set(value);
}

void raster::registerConsole(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "printLine", console::printLine);
    AttachFunction(object, "print", console::print);
    AttachFunction(object, "read", console::read);
}