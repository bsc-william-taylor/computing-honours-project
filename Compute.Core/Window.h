#pragma once

#include "ComputeCore.h"
#include "JsObject.h"

class Window : public JsObject<Window> 
{
    static v8::Persistent<v8::ObjectTemplate> objectTemplate;
    static v8::Persistent<v8::Function> constructor;

    std::string windowTitle;
    SDL_GLContext context;
    SDL_Window * window;
    SDL_Rect rect;
    SDL_bool fullscreen;
public:
    Window();
    ~Window();

    static void create(v8::Local<v8::Object>& cpp, v8::Isolate * isolate);

    static void enableOpenGL(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void newWindow(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void swapBuffers(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void setPosition(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void setTitle(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void setSize(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void onFrame(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void hide(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void show(const v8::FunctionCallbackInfo<v8::Value>& args);

    void destroy()
    {
        if(window != nullptr) 
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }
};