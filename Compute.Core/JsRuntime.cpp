
#include "JsRuntime.h"
#include "Modules.h"
#include "gl/GL.h"
#include "JsArrayAllocater.h"
#include "Fs.h"
#include "JsExtensions.h"

using namespace compute;

JsPlatform JsRuntime::platform;

JsRuntime::JsRuntime(std::vector<std::string>& args)
{
    initialise(args);
}

JsRuntime::~JsRuntime()
{
}

void JsRuntime::executeScriptMode(v8::Isolate* isolate, v8::Local<v8::Context> context, v8::Local<v8::String> source)
{
    v8::TryCatch trycatch(isolate);
    v8::Local<v8::Script> script;
    v8::Local<v8::Value> output;

    if (!v8::Script::Compile(context, source).ToLocal(&script))
    {
        CatchExceptions(trycatch);
    }
    else if (!script->Run(context).ToLocal(&output))
    {
        CatchExceptions(trycatch);
    }

    while (platform.PumpMessageLoop(isolate));
}

void JsRuntime::executeRepMode(v8::Isolate* isolate, v8::Local<v8::Context> context)
{
    std::string enteredLine;
    std::cout << "> ";

    while (getline(std::cin, enteredLine)) {
        v8::TryCatch trycatch(isolate);
        v8::Local<v8::Script> script;
        v8::Local<v8::Value> output;
        v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, enteredLine.c_str());

        if (!v8::Script::Compile(context, source).ToLocal(&script)) {
            CatchExceptions(trycatch);
            break;
        }

        if (!script->Run(context).ToLocal(&output)) {
            CatchExceptions(trycatch);
            break;
        }

        std::cout << *v8::String::Utf8Value(output->ToString()) << std::endl;
        std::cout << "> ";

        while (platform.PumpMessageLoop(isolate));
    }
}

void JsRuntime::start(std::string filename)
{
    auto scriptSrc = readFile(filename.c_str());

    ArrayBufferAllocator allocator;
    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = &allocator;
    auto isolate = v8::Isolate::New(createParams);
    {
        v8::Isolate::Scope isolateScope(isolate);
        v8::HandleScope handleScope(isolate);

        auto moduleTemplate = registerCommonJsModules();
        auto context = v8::Context::New(isolate, nullptr, moduleTemplate);
        auto scope = v8::Context::Scope(context);

        const auto src = v8::String::NewFromUtf8(isolate, scriptSrc.c_str());
        filename.empty() ? executeRepMode(isolate, context) : executeScriptMode(isolate, context, src);
        clearCommonJsModules();
    }

    isolate->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
    isolate->Dispose();

    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
}

void JsRuntime::initialise(std::vector<std::string>& args)
{
    auto argc{ static_cast<int>(args.size()) };
    auto argv{ new char *[argc] };

    for (auto i{ 0 }; i < argc; ++i)
    {
        argv[i] = const_cast<char *>(args[i].c_str());
    }

    const auto v8Flags = "--expose_gc --expose_debug_as=v8debug";

    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    v8::V8::SetFlagsFromString(v8Flags, strlen(v8Flags));
    v8::V8::SetFlagsFromCommandLine(&argc, argv, false);
    v8::V8::InitializePlatform(&platform);
    v8::V8::Initialize();

    delete[] argv;
}

JsPlatform& JsRuntime::getPlatform()
{
    return platform;
}