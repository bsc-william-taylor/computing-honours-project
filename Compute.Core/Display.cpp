
#include "Display.h"
#include "JsRuntime.h"
#include "JsExtensions.h"

using namespace compute;

void openMessage(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto function = GetFunction(args[2]);
        auto title = GetString(args[0]);
        auto body = GetString(args[1]);

        SDL_ShowSimpleMessageBox(0, title.c_str(), body.c_str(), nullptr);

        function->Call(function, 0, nullptr);
    }
}

const auto Show = [](v8::PersistentCopyable window, v8::PersistentCopyable callback)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto function = callback.Get(isolate);

    v8::Local<v8::Value> args[1];
    args[0] = window.Get(isolate);
    function->Call(function, 1, args);
};

const auto OnQuit = [](v8::PersistentCopyable window)
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

void openWindow(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 2)
    {
        auto windowCallback = GetFunction(args[1]);
        auto windowObject = GetFunction(args[0]);

        v8::PersistentCopyable callback;
        v8::PersistentCopyable window;

        callback.Reset(args.GetIsolate(), windowCallback);
        window.Reset(args.GetIsolate(), windowObject);

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

void compute::registerDisplay(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "displayInfo", displayInfo);
    AttachFunction(object, "openMessage", openMessage);
    AttachFunction(object, "openWindow", openWindow);

    Window::create(object, v8::Isolate::GetCurrent());
}