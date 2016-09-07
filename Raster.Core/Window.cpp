
#include "Window.h"
#include "JsRuntime.h"
#include "JsExtensions.h"

using namespace raster;

v8::Persistent<v8::ObjectTemplate> Window::objectTemplate;
v8::Persistent<v8::Function> Window::constructor;

void raster::showMessageBox(const v8::FunctionCallbackInfo<v8::Value>& args) {
	if (args.Length() == 3) {
		v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
		callback.Reset(v8::Isolate::GetCurrent(), args[2].As<v8::Function>());
		v8::String::Utf8Value title(args[0]);
		v8::String::Utf8Value body(args[1]);
		
		auto strTitle = std::string(*title);
		auto strBody = std::string(*body);

		SDL_ShowSimpleMessageBox(NULL, strTitle.c_str(), strBody.c_str(), nullptr);
		auto function = callback.Get(v8::Isolate::GetCurrent());
		function->Call(function, 0, nullptr);
	}
}

void raster::createWindow(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() == 2)
	{
		auto windowCallback = args[1].As<v8::Function>();
		auto windowObject = args[0].As<v8::Object>();	

		v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
		v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>> window;
        v8::Isolate * isolate = v8::Isolate::GetCurrent();

		callback.Reset(isolate, windowCallback);
		window.Reset(isolate, windowObject);

        auto& platform = JsRuntime::getPlatform();

        platform.CallOnForegroundThread(isolate, new JsAsyncTask([=]() {
            v8::Local<v8::Value> parameters[1] = { window.Get(v8::Isolate::GetCurrent()) };
            auto callbackFunction = callback.Get(v8::Isolate::GetCurrent());
            callbackFunction->Call(callbackFunction, 1, parameters);
        }));
		
        platform.CallOnForegroundThread(isolate, new JsAwaitTask([=](SDL_Event& ev) {
            if (ev.type == SDL_QUIT) {
                auto windowJs = window.Get(v8::Isolate::GetCurrent());
                auto wnd = Window::unwrap(windowJs);
                SDL_DestroyWindow(wnd->getWindow());
                return true;
            }

            return false;
        }));
	}
}

Window::Window() : 
    context(nullptr), 
    window(nullptr)
{
}

Window::~Window()
{
}

void Window::create(v8::Local<v8::Object>& raster, v8::Isolate * isolate)
{
    if(constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newWindow));
    }

    raster->Set(v8::String::NewFromUtf8(isolate, "Window"), constructor.Get(isolate));
}

void Window::newWindow(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();    
	auto object = newTemplate(objectTemplate);

    object->Set(V8_String("enableOpenGL"), v8::Function::New(isolate, enableOpenGL));
    object->Set(V8_String("swapBuffers"), v8::Function::New(isolate, swapBuffers));
    object->Set(V8_String("setPosition"), v8::Function::New(isolate, setPosition));
    object->Set(V8_String("setTitle"), v8::Function::New(isolate, setTitle));
    object->Set(V8_String("onFrame"), v8::Function::New(isolate, onFrame));
    object->Set(V8_String("setSize"), v8::Function::New(isolate, setSize));
    object->Set(V8_String("show"), v8::Function::New(isolate, show));
    object->Set(V8_String("hide"), v8::Function::New(isolate, hide));

	auto window = new Window();
	auto args = info[0].As<v8::Object>();
	auto t = args->Get(V8_String("title"));
	auto x = args->Get(V8_String("x"));
	auto y = args->Get(V8_String("y"));
	auto w = args->Get(V8_String("w"));
	auto h = args->Get(V8_String("h"));

	window->windowTitle = std::string(*v8::String::Utf8Value(t));
	window->rect.x = x->Int32Value();
	window->rect.y = y->Int32Value();
	window->rect.w = w->Int32Value();
	window->rect.h = h->Int32Value();
	window->wrap(object);

	info.GetReturnValue().Set(object);
}

void Window::setSize(const v8::FunctionCallbackInfo<v8::Value>& args) {
	auto that = unwrap(args);
	auto w = (*args[0])->ToInteger()->Value();
	auto h = (*args[1])->ToInteger()->Value();

	if (that->window == nullptr) {
		that->rect.w = w;
		that->rect.h = h;
	} else {
		SDL_SetWindowSize(that->window, w, h);
	}
}

void Window::setPosition(const v8::FunctionCallbackInfo<v8::Value>& args) {
	auto that = unwrap(args);
	auto x = (*args[0])->ToInteger()->Value();
	auto y = (*args[1])->ToInteger()->Value();

	if (that->window == nullptr) {
		that->rect.x = x;
		that->rect.y = y;
	} else {
		SDL_SetWindowPosition(that->window, x, y);
	}
}

void Window::onFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
	callback.Reset(v8::Isolate::GetCurrent(), args[0].As<v8::Function>());

    auto& platform = JsRuntime::getPlatform();
    auto isolate = v8::Isolate::GetCurrent();

    platform.CallOnForegroundThread(isolate, new JsRepeatTask([=]() {
        auto function = callback.Get(isolate);
        v8::TryCatch trycatch(isolate);
        function->Call(function, 0, nullptr);
        CatchExceptions(trycatch);
    }));
}

void Window::swapBuffers(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto object = unwrap(args);
	auto window = object->window;
	SDL_GL_SwapWindow(window);
}

void Window::show(const v8::FunctionCallbackInfo<v8::Value>& args) {
	auto object = unwrap(args);
	auto window = object->window;

	if (window == nullptr)
	{
		object->window = SDL_CreateWindow(
			object->windowTitle.c_str(),
			object->rect.x, object->rect.y,
			object->rect.w, object->rect.h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);
	}
	else
	{
		SDL_ShowWindow(window);
	}
}

void Window::enableOpenGL(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto object = unwrap(args);

	if(object->context == nullptr && object->window != nullptr)
	{
		object->context = SDL_GL_CreateContext(object->window);

		auto result = SDL_GL_SetSwapInterval(1);

		if(result != 0)
		{
			std::cout << "Error VSync not supported " << SDL_GetError() << std::endl;
		}
	}
}

void Window::hide(const v8::FunctionCallbackInfo<v8::Value>& args) {
	auto that = unwrap(args);
	auto window = that->window;

	if (window != nullptr)
	{
		SDL_HideWindow(window);
	}
}

void Window::setTitle(const v8::FunctionCallbackInfo<v8::Value>& args) {
	auto that = unwrap(args);
	v8::String::Utf8Value str(args[0]);
	that->windowTitle = std::string(*str);
	if (that->window != nullptr)
	{
		SDL_SetWindowTitle(that->window, that->windowTitle.c_str());
	}
}

void raster::registerDisplay(v8::Local<v8::Object>& object) {
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(V8_String("showMessageBox"), v8::Function::New(isolate, showMessageBox));
    object->Set(V8_String("createWindow"), v8::Function::New(isolate, createWindow));

    Window::create(object, isolate);
}