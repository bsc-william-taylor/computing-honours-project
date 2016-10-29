
#include "Display.h"
#include "JsRuntime.h"
#include "JsExtensions.h"

using namespace compute;

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

void Window::newWindow(v8::FunctionArgs info)
{
    auto object = newTemplate(objectTemplate);

    AttachFunction(object, "enableOpenGL", enableOpenGL);
    AttachFunction(object, "swapBuffers", swapBuffers);
    AttachFunction(object, "setPosition", setPosition);
    AttachFunction(object, "setTitle", setTitle);
    AttachFunction(object, "onFrame", onFrame);
    AttachFunction(object, "setSize", setSize);
    AttachFunction(object, "show", show);
    AttachFunction(object, "hide", hide);

    auto args = GetObject(info[0]);
    auto fullscreen = args->Get(v8::NewString("fullscreen"));
    auto title = args->Get(v8::NewString("title"));

    auto window = new Window();
    window->fullscreen = fullscreen->BooleanValue() ? SDL_TRUE : SDL_FALSE;
    window->rect.x = args->Get(v8::NewString("x"))->Int32Value();
    window->rect.y = args->Get(v8::NewString("y"))->Int32Value();
    window->rect.w = args->Get(v8::NewString("w"))->Int32Value();
    window->rect.h = args->Get(v8::NewString("h"))->Int32Value();
    window->title = std::string(*v8::String::Utf8Value(title));
    window->wrap(object);

    info.GetReturnValue().Set(object);
}

void Window::setSize(v8::FunctionArgs args)
{
    auto object = unwrap(args);
    auto w = GetNumber(args[0]);
    auto h = GetNumber(args[1]);

    if (object->window == nullptr)
    {
        object->rect.w = w;
        object->rect.h = h;
    }
    else
    {
        SDL_SetWindowSize(object->window, w, h);
    }
}

void Window::setPosition(v8::FunctionArgs args)
{
    const auto object = unwrap(args);
    const auto x = GetNumber(args[0]);
    const auto y = GetNumber(args[1]);

    if (object->window == nullptr)
    {
        object->rect.x = x;
        object->rect.y = y;
    }
    else
    {
        SDL_SetWindowPosition(object->window, x, y);
    }
}

const auto Render = [](auto window, auto callback, auto isolate)
{
    const auto instance = JsObject<Window>::unwrap(window.Get(isolate));
    const auto function = callback.Get(isolate);

    v8::TryCatch trycatch(isolate);
    function->Call(function, 0, nullptr);
    CatchExceptions(trycatch);
    return !instance->hasWindow();
};

void Window::onFrame(v8::FunctionArgs args)
{
    v8::PersistentCopyable window(args.GetIsolate(), args.This().As<v8::Function>());
    v8::PersistentCopyable callback(args.GetIsolate(), args[0].As<v8::Function>());
    v8::OnForeground(Render, window, callback, args.GetIsolate());
}

void Window::swapBuffers(v8::FunctionArgs args)
{
    auto object = unwrap(args);
    auto window = object->window;

    if (window != nullptr)
    {
        SDL_GL_SwapWindow(window);
    }
}

void Window::show(v8::FunctionArgs args)
{
    auto object = unwrap(args);

    if (object->window == nullptr)
    {
        const auto title = object->title.c_str();
        const auto p = object->rect;

        const auto window = SDL_CreateWindow(title, p.x, p.y, p.w, p.h, SDL_WINDOW_OPENGL);

        if (object->fullscreen && window != nullptr)
        {
            SDL_SetWindowBordered(window, SDL_FALSE);
        }

        object->window = window;
    }

    SDL_ShowWindow(object->window);
}

void Window::enableOpenGL(v8::FunctionArgs args)
{
    auto object = unwrap(args);

    if (object->context == nullptr && object->window != nullptr)
    {
        const auto context = SDL_GL_CreateContext(object->window);

        SDL_GL_MakeCurrent(object->window, context);
        SDL_GL_SetSwapInterval(1);

        object->context = context;
    }
}

void Window::hide(v8::FunctionArgs args)
{
    const auto window = unwrap(args)->window;

    if (window != nullptr)
    {
        SDL_HideWindow(window);
    }
}

void Window::setTitle(v8::FunctionArgs args)
{
    const auto title = GetString(args[0]);
    const auto object = unwrap(args);
    object->title = title;

    if (object->window != nullptr)
    {
        SDL_SetWindowTitle(object->window, title.c_str());
    }
}

void Window::destroy()
{
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

bool Window::hasWindow()
{
    return window != nullptr;
}

const auto Show = [](auto window, auto callback)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto function = callback.Get(isolate);

    v8::TryCatch trycatch(isolate);
    v8::Local<v8::Value> args[1];
    args[0] = window.Get(isolate);
    function->Call(function, 1, args);
    CatchExceptions(trycatch);
};

const auto OpenMessage = [](auto title, auto body, auto callback)
{   
    SDL_ShowSimpleMessageBox(0, title.c_str(), body.c_str(), nullptr);
    auto function = callback.Get(v8::Isolate::GetCurrent());
    function->Call(function, 0, nullptr);
};

const auto OnQuit = [](auto window)
{
    auto& events = JsRuntime::getPlatform().GetSystemEvents();

    for (auto& ev : events)
    {
        if (ev.type == SDL_QUIT || ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)
        {
            auto object = window.Get(v8::Isolate::GetCurrent());
            auto screen = Window::unwrap(object);
            screen->destroy();
            return true;
        }
    }

    return false;
};

void openMessage(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto title = GetString(args[0]);
        auto body = GetString(args[1]);

        v8::PersistentCopyable callback(args.GetIsolate(), GetFunction(args[2]));
        v8::OnForeground<JsAsyncTask>(OpenMessage, title, body, callback);
    }
}

void openWindow(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 2)
    {
        auto windowCallback = GetFunction(args[1]);
        auto windowObject = GetFunction(args[0]);

        v8::PersistentCopyable callback(args.GetIsolate(), windowCallback);
        v8::PersistentCopyable window(args.GetIsolate(), windowObject);
        v8::OnForeground<JsAsyncTask>(Show, window, callback);
        v8::OnForeground(OnQuit, window);
    }
}

void displayInfo(v8::FunctionArgs args)
{
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        v8::Throw("SDL_GetDesktopDisplayMode failed");
    }

    const auto data = v8::Object::New(args.GetIsolate());
    data->Set(v8::NewString("refreshRate"), v8::NewNumber(dm.refresh_rate));
    data->Set(v8::NewString("h"), v8::NewNumber(dm.h));
    data->Set(v8::NewString("w"), v8::NewNumber(dm.w));
    args.GetReturnValue().Set(data);
}

void compute::registerDisplay(v8::Exports exports)
{
    AttachFunction(exports, "displayInfo", displayInfo);
    AttachFunction(exports, "openMessage", openMessage);
    AttachFunction(exports, "openWindow", openWindow);

    Window::create(exports, v8::Isolate::GetCurrent());
}