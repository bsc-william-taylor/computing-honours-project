
#include "Display.h"
#include "JsRuntime.h"
#include "JsExtensions.h"

using namespace raster;

void display::showMessageBox(const v8::FunctionCallbackInfo<v8::Value>& args) {
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

void display::createWindow(const v8::FunctionCallbackInfo<v8::Value>& args)
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

        platform.CallOnForegroundThread(isolate, new JsAwaitTask([=]() {
            auto& events = JsRuntime::getPlatform().GetSystemEvents();
            for(auto& ev : events)
            {
                if (ev.type == SDL_QUIT) 
                {
                    auto windowJs = window.Get(v8::Isolate::GetCurrent());
                    auto wnd = Window::unwrap(windowJs);
                    SDL_DestroyWindow(wnd->getWindow());
                    return true;
                }
            }
           
            return false;
        }));
    }
}

void raster::registerDisplay(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "showMessageBox", display::showMessageBox);
    AttachFunction(object, "createWindow", display::createWindow);

    Window::create(object, v8::Isolate::GetCurrent());
}