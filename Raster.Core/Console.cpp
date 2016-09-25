
#include "Console.h"
#include "JsExtensions.h"

void raster::console::printLine(v8::FunctionArgs args)
{
    const auto argLength = args.Length();

    for (auto i{ 0 }; i < argLength; ++i)
    {
        if (args[i]->IsString())
        {
            std::cout << GetString(args[i]) << std::endl;
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
            std::cout << GetString(args[i]);
        }
    }
}

void raster::console::read(v8::FunctionArgs args)
{
    std::string input;
    std::getline(std::cin, input);
    args.GetReturnValue().Set(v8::NewString(input.c_str()));
}

void raster::registerConsole(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "printLine", console::printLine);
    AttachFunction(object, "print", console::print);
    AttachFunction(object, "read", console::read);
}