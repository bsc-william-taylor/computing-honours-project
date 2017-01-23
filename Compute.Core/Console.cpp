
#include "Console.h"
#include "JsExtensions.h"

void printLine(v8::FunctionArgs args)
{
    const auto argLength = args.Length();

    for (auto i{ 0 }; i < argLength; ++i)
    {
        if (args[i]->IsString())
        {
            printf((GetString(args[i]) + "\n").c_str());
        }
    }
}

void clear(v8::FunctionArgs args)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print(v8::FunctionArgs args)
{
    const auto argLength = args.Length();

    for (auto i{ 0 }; i < argLength; ++i)
    {
        if (args[i]->IsString())
        {
            printf(GetString(args[i]).c_str());
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
    AttachFunction(exports, "clear", clear);
}