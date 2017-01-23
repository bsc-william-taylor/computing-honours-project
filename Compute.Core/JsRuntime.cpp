
#include "JsRuntime.h"
#include "Modules.h"
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

void JsRuntime::launchScript(v8::Isolate* isolate, v8::Local<v8::Context> context, v8::Local<v8::String> source)
{
    v8::TryCatch trycatch(isolate);
    v8::Local<v8::Script> script;
    v8::Local<v8::Value> output;

    if (!v8::Script::Compile(context, source).ToLocal(&script))
    {
        CatchExceptions(trycatch);
    }

    if (!script->Run(context).ToLocal(&output))
    {
        CatchExceptions(trycatch);
    }

    while (platform.PumpMessageLoop(isolate));
}

void JsRuntime::launchREPL(v8::Isolate* isolate, v8::Local<v8::Context> context)
{
    std::string enteredLine;
    std::cout << "> ";

    while (getline(std::cin, enteredLine)) {
        if(enteredLine == "quit")
            break;

        v8::TryCatch trycatch(isolate);
        v8::Local<v8::Script> script;
        v8::Local<v8::Value> output;
        v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, enteredLine.c_str());

        if (!v8::Script::Compile(context, source).ToLocal(&script)) {
            CatchExceptions(trycatch);
        } else if (!script->Run(context).ToLocal(&output)) {
            CatchExceptions(trycatch);
        } else {
            std::cout << GetString(output->ToString()) << std::endl;
        }

        std::cout << "> ";

        while (platform.PumpMessageLoop(isolate));
    }
}

void JsRuntime::start(std::string filename)
{
    ArrayBufferAllocator allocator;
    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = &allocator;
   
    auto isolate = v8::Isolate::New(createParams);
    {
        v8::Isolate::Scope isolateScope(isolate);
        v8::HandleScope handleScope(isolate);

        const auto fileProvided = filename.empty();
        const auto moduleTemplate = registerCommonJsModules();
        const auto context = v8::Context::New(isolate, nullptr, moduleTemplate);
        const auto scope = v8::Context::Scope(context);

        const auto src = v8::NewString(readStartupFile(filename.c_str()));

        if(fileProvided)
        {
            launchScript(isolate, context, src);
        }
        else
        {
            launchREPL(isolate, context);
        }

        releaseModuleCache();
    }

    //isolate->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
    isolate->LowMemoryNotification();
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

    const auto v8Flags = "--expose_gc --expose-debug-as=v8debug --trace-hydrogen-file=hydrogen.cfg --trace-turbo-cfg-file=turbo.cfg --redirect-code-traces-to=code.asm";

    v8::V8::InitializeExternalStartupData(argv[0]);
    v8::V8::SetFlagsFromString(v8Flags, strlen(v8Flags));
    v8::V8::InitializePlatform(&platform);
    v8::V8::Initialize();

    delete[] argv;
}

JsPlatform& JsRuntime::getPlatform()
{
    return platform;
}