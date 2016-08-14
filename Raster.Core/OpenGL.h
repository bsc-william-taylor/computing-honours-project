#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster {
	void perspective(const v8::FunctionCallbackInfo<v8::Value>& args);
	void loadIdentity(const v8::FunctionCallbackInfo<v8::Value>& args);
	void matrixMode(const v8::FunctionCallbackInfo<v8::Value>& args);
	void translate(const v8::FunctionCallbackInfo<v8::Value>& args);
	void rotate(const v8::FunctionCallbackInfo<v8::Value>& args);

	void clearColor(const v8::FunctionCallbackInfo<v8::Value>& args);
	void vertex2f(const v8::FunctionCallbackInfo<v8::Value>& args);
	void vertex3f(const v8::FunctionCallbackInfo<v8::Value>& args);
	void color3f(const v8::FunctionCallbackInfo<v8::Value>& args);
	void clear(const v8::FunctionCallbackInfo<v8::Value>& args);
	void enable(const v8::FunctionCallbackInfo<v8::Value>& args);
	void begin(const v8::FunctionCallbackInfo<v8::Value>& args);
	void end(const v8::FunctionCallbackInfo<v8::Value>& args);


	static void setupOpenglModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		object->Set(V8_String("gluPerspective"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), perspective));
		object->Set(V8_String("glEnable"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), enable));
		object->Set(V8_String("glMatrixMode"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), matrixMode));
		object->Set(V8_String("glLoadIdentity"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), loadIdentity));
		object->Set(V8_String("glTranslatef"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), translate));
		object->Set(V8_String("glRotatef"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), rotate));
		object->Set(V8_String("glClearColor"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), clearColor));
		object->Set(V8_String("glVertex3f"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), vertex3f));
		object->Set(V8_String("glVertex2f"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), vertex2f));
		object->Set(V8_String("glColor3f"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), color3f));
		object->Set(V8_String("glClear"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), clear));
		object->Set(V8_String("glBegin"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), begin));
		object->Set(V8_String("glEnd"), v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), end));
	}
}