
#include "OpenGL.h"
#include "gl/GLU.h"
#include "gl/gl.h"

void raster::glClearColor(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 4)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();
        auto a = args[3].As<v8::Number>()->Value();

        ::glClearColor(r, g, b, a);
    }
}

void raster::glClear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glClear(args[0]->NumberValue());
    }
}

void raster::glBegin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glBegin(static_cast<GLenum>(args[0]->NumberValue()));
    }
}

void raster::glColor3(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();

        glColor3f(r, g, b);
    }
}

void raster::glVertex2(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 2)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();

        glVertex2f(x, y);
    }
}

void raster::glVertex3(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glVertex3f(x, y, z);
    }
}

void raster::glLoadIdentity(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ::glLoadIdentity();
}

void raster::glMatrixMode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glMatrixMode(args[0].As<v8::Number>()->Value());
    }
}

void raster::glTranslate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glTranslatef(x, y, z);
    }
}

void raster::glRotate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 4)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto x = args[1].As<v8::Number>()->Value();
        auto y = args[2].As<v8::Number>()->Value();
        auto z = args[3].As<v8::Number>()->Value();

        glRotatef(r, x, y, z);
    }
}

void raster::glPerspective(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 4)
    {
        auto fov = args[0].As<v8::Number>()->Value();
        auto aspect = args[1].As<v8::Number>()->Value();
        auto min = args[2].As<v8::Number>()->Value();
        auto max = args[3].As<v8::Number>()->Value();

        gluPerspective(fov, aspect, min, max);
    }
}

void raster::glEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ::glEnd();
}

void raster::glEnable(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glEnable(args[0].As<v8::Integer>()->Value());
    }

}

void raster::registerOpenGL(v8::Local<v8::Object>& object) {
    object->Set(V8_String("gluPerspective"), v8::Function::New(v8::Isolate::GetCurrent(), glPerspective));
    object->Set(V8_String("glEnable"), v8::Function::New(v8::Isolate::GetCurrent(), glEnable));
    object->Set(V8_String("glMatrixMode"), v8::Function::New(v8::Isolate::GetCurrent(), glMatrixMode));
    object->Set(V8_String("glLoadIdentity"), v8::Function::New(v8::Isolate::GetCurrent(), glLoadIdentity));
    object->Set(V8_String("glTranslatef"), v8::Function::New(v8::Isolate::GetCurrent(), glTranslate));
    object->Set(V8_String("glRotatef"), v8::Function::New(v8::Isolate::GetCurrent(), glRotate));
    object->Set(V8_String("glClearColor"), v8::Function::New(v8::Isolate::GetCurrent(), glClearColor));
    object->Set(V8_String("glVertex3f"), v8::Function::New(v8::Isolate::GetCurrent(), glVertex3));
    object->Set(V8_String("glVertex2f"), v8::Function::New(v8::Isolate::GetCurrent(), glVertex2));
    object->Set(V8_String("glColor3f"), v8::Function::New(v8::Isolate::GetCurrent(), glColor3));
    object->Set(V8_String("glClear"), v8::Function::New(v8::Isolate::GetCurrent(), glClear));
    object->Set(V8_String("glBegin"), v8::Function::New(v8::Isolate::GetCurrent(), glBegin));
    object->Set(V8_String("glEnd"), v8::Function::New(v8::Isolate::GetCurrent(), glEnd));
}