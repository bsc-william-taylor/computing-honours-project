#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster {
	void showMessageBox(const v8::FunctionCallbackInfo<v8::Value>& args);
	void createWindow(const v8::FunctionCallbackInfo<v8::Value>& args);

	class Window : public JsObject<Window> {
        static v8::Global<v8::ObjectTemplate> objectTemplate;
		static v8::Global<v8::Function> constructor;

		std::string windowTitle;
		SDL_GLContext context;
		SDL_Window * window;
		SDL_Rect rect;
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
		
		SDL_Window * getWindow() const {
			return window;
		}
	};

	static void setupDisplayModule(v8::Isolate * isolate, v8::Local<v8::Object>& object) {
		object->Set(V8_String("showMessageBox"), v8::Function::New(isolate, showMessageBox));
		object->Set(V8_String("createWindow"), v8::Function::New(isolate, createWindow));

		Window::create(object, isolate);
	}
}