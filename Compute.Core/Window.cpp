
#include "Window.h"
#include "JsRuntime.h"
#include "JsExtensions.h"

v8::Persistent<v8::ObjectTemplate> Window::objectTemplate;
v8::Persistent<v8::Function> Window::constructor;

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
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newWindow));
    }

    raster->Set(v8::String::NewFromUtf8(isolate, "Window"), constructor.Get(isolate));
}

void Window::newWindow(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    auto object = newTemplate(objectTemplate);

    object->Set(v8::NewString("enableOpenGL"), v8::Function::New(isolate, enableOpenGL));
    object->Set(v8::NewString("swapBuffers"), v8::Function::New(isolate, swapBuffers));
    object->Set(v8::NewString("setPosition"), v8::Function::New(isolate, setPosition));
    object->Set(v8::NewString("setTitle"), v8::Function::New(isolate, setTitle));
    object->Set(v8::NewString("onFrame"), v8::Function::New(isolate, onFrame));
    object->Set(v8::NewString("setSize"), v8::Function::New(isolate, setSize));
    object->Set(v8::NewString("show"), v8::Function::New(isolate, show));
    object->Set(v8::NewString("hide"), v8::Function::New(isolate, hide));

    auto window = new Window();
    auto args = info[0].As<v8::Object>();
    auto fullscreen = args->Get(v8::NewString("fullscreen"));
    auto t = args->Get(v8::NewString("title"));
    auto x = args->Get(v8::NewString("x"));
    auto y = args->Get(v8::NewString("y"));
    auto w = args->Get(v8::NewString("w"));
    auto h = args->Get(v8::NewString("h"));

    window->fullscreen = fullscreen->BooleanValue() ? SDL_TRUE : SDL_FALSE;
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
    }
    else {
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
    }
    else {
        SDL_SetWindowPosition(that->window, x, y);
    }
}

void Window::onFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
    callback.Reset(v8::Isolate::GetCurrent(), args[0].As<v8::Function>());

    v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>> window;
    window.Reset(v8::Isolate::GetCurrent(), args.This());
  
    auto& platform = compute::JsRuntime::getPlatform();
    auto isolate = v8::Isolate::GetCurrent();

    platform.CallOnForegroundThread(isolate, new JsAwaitTask([=]() {
        auto parent = window.Get(isolate);
        auto instance = unwrap(parent);
        auto function = callback.Get(isolate);

        v8::TryCatch trycatch(isolate);
        function->Call(function, 0, nullptr);
        CatchExceptions(trycatch);
        return !instance->window;
    }));
}

void Window::swapBuffers(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto object = unwrap(args);
    auto window = object->window;

    if(window != nullptr)
    {
        SDL_GL_SwapWindow(window);
    }
}

void Window::show(const v8::FunctionCallbackInfo<v8::Value>& args) {
    auto object = unwrap(args);

    if (object->window == nullptr)
    {
        object->window = SDL_CreateWindow(
            object->windowTitle.c_str(),
            object->rect.x, object->rect.y,
            object->rect.w, object->rect.h,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        if(object->fullscreen && object->window != nullptr)
        {
            SDL_SetWindowFullscreen(object->window, SDL_WINDOW_FULLSCREEN);
        }
    }
    else
    {
        if(object->window != nullptr)
        {
            SDL_ShowWindow(object->window);
        }
    }
}

void Window::enableOpenGL(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto object = unwrap(args);

    if (object->context == nullptr && object->window != nullptr)
    {
        object->context = SDL_GL_CreateContext(object->window);

        auto result = SDL_GL_SetSwapInterval(1);

        if (result != 0)
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
