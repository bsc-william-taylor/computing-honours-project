#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster {
	void showMessageBox(const v8::FunctionCallbackInfo<v8::Value>& args);
	void createWindow(const v8::FunctionCallbackInfo<v8::Value>& args);

	class Window : public JsObject<Window> {
		static v8::Persistent<v8::Function> constructor;
		std::string windowTitle;
		SDL_GLContext context;
		SDL_Window * window;
		SDL_Rect rect;
	public:
		Window();
		~Window();

		static void enableOpenGL(const v8::FunctionCallbackInfo<v8::Value>& args);
		static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);
		static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
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

	static void setupDisplayModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		object->Set(V8_String("showMessageBox"), v8::FunctionTemplate::New(isolate, showMessageBox));
		object->Set(V8_String("createWindow"), v8::FunctionTemplate::New(isolate, createWindow));

		Window::create(object, isolate);
	}
}

/*
// Properties
//templateObject->InstanceTemplate()->SetAccessor(V8_String("name"), get, set);

static void get(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
auto that = info.This();
const Window * obj = unwrap(that);
auto isolate = v8::Isolate::GetCurrent();
auto value = v8::String::NewFromUtf8(isolate, obj->name.c_str());
info.GetReturnValue().Set(value);
}

static void set(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info) {
auto that = info.This();
auto obj = unwrap(that);
v8::String::Utf8Value newValue(value);
obj->name = std::string(*newValue);
}*/
