
#include "JsRuntime.h"
#include "Modules.h"
#include "JsArrayAllocater.h"
#include "Fs.h"
#include "JsExtensions.h"
#include "JsDebug.h"
#include "Debug.h"

using namespace compute;

JsPlatform JsRuntime::platform;

JsRuntime::JsRuntime(std::vector<std::string>& args)
{
    initialise(args);
}

JsRuntime::~JsRuntime()
{
}

void LogCallback(const char* name, int event)
{
/*
    std::ofstream fileLog("./log.txt", std::ios::out | std::ios::app);
    fileLog << name << event << std::endl;
    fileLog.close();
*/
}

void JsRuntime::executeScriptMode(v8::Isolate* isolate, v8::Local<v8::Context> context, v8::Local<v8::String> source)
{
    v8::TryCatch trycatch(isolate);
    v8::Local<v8::Script> script;
    v8::Local<v8::Value> output;

    isolate->SetEventLogger(LogCallback);

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

v8::Isolate* createIsolate(v8::Isolate::CreateParams& params)
{
   return v8::Isolate::New(params);
}

void createHandles(v8::Isolate* isolate)
{
    // Create new handle
    v8::Local<v8::Number> number = v8::Number::New(isolate, 10.0);
    // Acquire raw value
    double v = number->Value();
    // Check if handle is a number
    bool b = number->IsNumber();
}

void createScope()
{
    // Handles are cleanup when scope is destroyed
    v8::HandleScope scope(v8::Isolate::GetCurrent());
}

void createContext(v8::Isolate* isolate)
{
    // Create the global obejct for the context
    auto global = v8::ObjectTemplate::New(isolate);

    // Create our JavaScript context which can execute code
    auto context = v8::Context::New(isolate, nullptr, global);
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

        auto moduleTemplate = registerCommonJsModules();
        auto context = v8::Context::New(isolate, nullptr, moduleTemplate);
        auto scope = v8::Context::Scope(context);

        _context.Reset(isolate, context);
    
        const auto src = v8::NewString(readStartupFile(filename.c_str()));
        filename.empty() ? executeRepMode(isolate, context) : executeScriptMode(isolate, context, src);
        releaseModuleCache();
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