
#include "JsRuntime.h"
#include "Modules.h"
#include "gl/GL.h"
#include "JsArrayAllocater.h"

using namespace raster;

JsPlatform JsRuntime::platform;

JsRuntime::JsRuntime(std::vector<std::string>& args)
{
    initialise(args);
}

JsRuntime::~JsRuntime()
{
}

void JsRuntime::start()
{
    ArrayBufferAllocator allocator;
    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = &allocator;

    auto isolate = v8::Isolate::New(createParams);
    isolate->Enter();

    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);

    auto moduleTemplate = setupModuleSystem();
    auto context = v8::Context::New(isolate, nullptr, moduleTemplate);
    auto scope = v8::Context::Scope(context);
    
    std::string enteredLine;
    std::cout << "> ";
    while(getline(std::cin, enteredLine)) {
        v8::TryCatch trycatch(isolate);
        v8::Local<v8::Script> script;
        v8::Local<v8::Value> output;
        v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, enteredLine.c_str());

        if (!v8::Script::Compile(context, source).ToLocal(&script)) {
            printException(trycatch);
            break;
        } 

        if(!script->Run(context).ToLocal(&output)) {
            printException(trycatch);
            break;
        }

        std::cout << *v8::String::Utf8Value(output->ToString()) << std::endl;
        std::cout << "> ";

        while(platform.PumpMessageLoop(isolate));
    }

    clear();

    isolate->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
}

void JsRuntime::printException(const v8::TryCatch& trycatch)
{
    v8::String::Utf8Value exception_str(trycatch.Exception());
    const char * error = *exception_str;
    std::cerr << "Exception thrown: " << error << std::endl;
}

void JsRuntime::start(std::string filename)
{
	auto scriptSrc = readFile(filename.c_str());
	
    ArrayBufferAllocator allocator;
    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = &allocator;

    auto isolate = v8::Isolate::New(createParams);
	isolate->Enter();

	v8::Isolate::Scope isolate_scope(isolate);
	v8::HandleScope handle_scope(isolate);

    auto moduleTemplate = setupModuleSystem();
    auto context = v8::Context::New(isolate, nullptr, moduleTemplate);
    auto scope = v8::Context::Scope(context);

    v8::TryCatch trycatch(isolate);
    v8::Local<v8::Script> script;
    v8::Local<v8::Value> output;
    
    auto source = v8::String::NewFromUtf8(isolate, scriptSrc.c_str());

    if (!v8::Script::Compile(context, source).ToLocal(&script)) {
        printException(trycatch);
    } else if (!script->Run(context).ToLocal(&output)) {
        printException(trycatch);
    }

    while (platform.PumpMessageLoop(isolate))

    clear();
	isolate->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
}

void JsRuntime::initialise(std::vector<std::string>& args)
{
    auto argc { static_cast<int>(args.size()) };
    auto argv { new char *[argc] };

    for(auto i{0}; i < argc; ++i)
    {
        argv[i] = const_cast<char *>(args[i].c_str());
    }

    const auto v8Flags = "--expose_gc";

    v8::V8::InitializeICU();    
    v8::V8::InitializePlatform(&platform);
    v8::V8::SetFlagsFromString(v8Flags, strlen(v8Flags));
    v8::V8::SetFlagsFromCommandLine(&argc, argv, false);
    v8::V8::Initialize();

    delete[] argv;
}