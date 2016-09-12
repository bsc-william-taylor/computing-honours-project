#pragma once

#include "RasterCore.h"
#include "JsObject.h"

namespace raster 
{
    void glPerspective(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glLoadIdentity(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glMatrixMode(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glTranslate(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glRotate(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glClearColor(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glVertex2(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glVertex3(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glColor3(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glClear(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glEnable(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glBegin(const v8::FunctionCallbackInfo<v8::Value>& args);
    void glEnd(const v8::FunctionCallbackInfo<v8::Value>& args);

    void registerOpenGL(v8::Local<v8::Object>& object);
}