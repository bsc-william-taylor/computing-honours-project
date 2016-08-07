
#include "JavaScriptSubsystem.h"
#include "Modules.h"
#include "gl/GL.h"

using namespace raster;

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator
{
public:
    void * Allocate(size_t length) override {
        auto data = AllocateUninitialized(length);
        return data == nullptr ? data : memset(data, 0, length);
    }

    void * AllocateUninitialized(size_t length) override {
        return malloc(length);
    }

    void Free(void* data, size_t) override {
        free(data);
    }
};

std::vector<std::function<bool(SDL_Event)>> JavaScriptSubsystem::eventHooks;

std::string readFile(const char * filename)
{
	std::ifstream file(filename);
	std::string data;

	if (file.is_open()) {
		std::string temp;
		while (getline(file, temp)) {
			data += temp + "\n";
		}

		file.close();
	}

	return data;
}

JavaScriptSubsystem::JavaScriptSubsystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(SDL_IMG_EVERYTHING);
}

JavaScriptSubsystem::~JavaScriptSubsystem()
{
	IMG_Quit();
	SDL_Quit();
}

void JavaScriptSubsystem::run(std::string filename)
{
	auto scriptSrc = readFile(filename.c_str());
	scriptSrc.append("(__bootstrap__());");

    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = new ArrayBufferAllocator();

	auto isolate = v8::Isolate::New(createParams);
    isolate = v8::Isolate::New(createParams);
	isolate->Enter();

	v8::Isolate::Scope isolate_scope(isolate);
	v8::HandleScope handle_scope(isolate);

    auto source = v8::String::NewFromUtf8(isolate, scriptSrc.c_str(), v8::NewStringType::kNormal).ToLocalChecked();
    auto moduleTemplate = setupModuleSystem();
    moduleTemplate->Set(V8_String("__bootstrap__"), v8::FunctionTemplate::New(isolate, beginMainEventLoop));

    auto context = v8::Context::New(isolate, nullptr, moduleTemplate);
    auto scope = v8::Context::Scope(context);

    v8::TryCatch trycatch(isolate);
    auto script = v8::Script::Compile(context, source).ToLocalChecked();

    if (script.IsEmpty()) {
        auto exception = trycatch.Exception();
        v8::String::Utf8Value exception_str(exception);
        std::cerr << *exception_str << std::endl;
    }
    else {
        auto result = script->Run(context);

        if (result.IsEmpty()) {
            auto exception = trycatch.Exception();
            v8::String::Utf8Value exception_str(exception);
            std::cerr << *exception_str << std::endl;
        }
    }

    clear();

	// Fix this delete is happening then events are trying to access the point
	isolate->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
}

void JavaScriptSubsystem::initialize(Poco::Util::Application& app)
{
    v8::V8::InitializeICU();
    
    auto platform = v8::platform::CreateDefaultPlatform();
    auto v8Flags = "--expose_gc";

    v8::V8::InitializePlatform(platform);
    v8::V8::SetFlagsFromString(v8Flags, strlen(v8Flags));
    v8::V8::Initialize();
}

const char * JavaScriptSubsystem::name() const
{
	return typeid(JavaScriptSubsystem).name();
};

void JavaScriptSubsystem::beginMainEventLoop(const v8::FunctionCallbackInfo<v8::Value>& value)
{
	if(value.Length() == 0)
	{
		auto renderMethod = std::function<void()>([](){});
		auto shutdown = false;

		while (!shutdown) {
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				for (auto i = 0; i < eventHooks.size(); i++) {
					if(eventHooks[i](e)) {
						eventHooks.erase(eventHooks.begin() + i);
					}
				}

				if(e.type == EVENT_CALLBACK) {
					auto functionPointer = e.user.data1;
					auto function = static_cast<std::function<void()> *>(functionPointer);
					(*function)();
					delete function;
				}

				if(e.type == TIMER_CHANGE)
				{
					auto functionPointer = static_cast<std::function<void()> *>(e.user.data1);
					renderMethod = *functionPointer;
					//fps = 1.0e9 / *static_cast<int *>(e.user.data2);
					delete functionPointer;
				}
			}

			
			renderMethod();
			
			if (eventHooks.empty()) {
				shutdown = true;
			}
		}
	}
}