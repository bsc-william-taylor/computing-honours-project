
#include "Console.h"
#include "JsExtensions.h"

void printLine(v8::FunctionArgs args)
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

void print(v8::FunctionArgs args)
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

void get(v8::FunctionArgs args)
{
    std::string input;
    std::getline(std::cin, input);
    args.GetReturnValue().Set(v8::NewString(input.c_str()));
}

void compute::registerConsole(v8::Exports exports)
{
    AttachFunction(exports, "printLine", printLine);
    AttachFunction(exports, "print", print);
    AttachFunction(exports, "read", get);
}