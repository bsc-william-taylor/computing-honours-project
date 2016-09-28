#pragma once

#include "ComputeCore.h"
#include "JsObject.h"
#include "JsExtensions.h"

namespace compute
{
    class Window : public JsObject<Window>
    {
        static v8::Persistent<v8::ObjectTemplate> objectTemplate;
        static v8::Persistent<v8::Function> constructor;

        SDL_GLContext context;
        SDL_Window* window;
        SDL_bool fullscreen;
        SDL_Rect rect;

        std::string title;
    public:
        Window();
        ~Window();

        bool hasWindow();

        static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);
        static void enableOpenGL(v8::FunctionArgs args);
        static void swapBuffers(v8::FunctionArgs args);
        static void setPosition(v8::FunctionArgs args);
        static void newWindow(v8::FunctionArgs args);
        static void setTitle(v8::FunctionArgs args);
        static void setSize(v8::FunctionArgs args);
        static void onFrame(v8::FunctionArgs args);
        static void hide(v8::FunctionArgs args);
        static void show(v8::FunctionArgs args);

        void destroy();
    };

    void registerDisplay(v8::Exports exports);
}