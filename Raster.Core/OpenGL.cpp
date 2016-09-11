
#include "OpenGL.h"
#include "gl/GLU.h"
#include "gl/gl.h"

void raster::clearColor(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 4)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();
        auto a = args[3].As<v8::Number>()->Value();

        glClearColor(r, g, b, a);
    }
}

void raster::clear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void raster::begin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        auto num = args[0].As<v8::Number>()->Value();
        glBegin(static_cast<unsigned int>(num));
    }
}

void raster::color3f(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();

        glColor3f(r, g, b);
    }
}

void raster::vertex2f(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 2)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();

        glVertex2f(x, y);
    }
}

void raster::vertex3f(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glVertex3f(x, y, z);
    }
}

void raster::loadIdentity(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    glLoadIdentity();
}

void raster::matrixMode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        glMatrixMode(args[0].As<v8::Number>()->Value());
    }
}

void raster::translate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glTranslatef(x, y, z);
    }
}

void raster::rotate(const v8::FunctionCallbackInfo<v8::Value>& args)
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

void raster::perspective(const v8::FunctionCallbackInfo<v8::Value>& args)
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

void raster::end(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    glEnd();
}

void raster::enable(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        glEnable(args[0].As<v8::Integer>()->Value());
    }

}

void raster::registerOpenGL(v8::Local<v8::Object>& object) {
    object->Set(V8_String("gluPerspective"), v8::Function::New(v8::Isolate::GetCurrent(), perspective));
    object->Set(V8_String("glEnable"), v8::Function::New(v8::Isolate::GetCurrent(), enable));
    object->Set(V8_String("glMatrixMode"), v8::Function::New(v8::Isolate::GetCurrent(), matrixMode));
    object->Set(V8_String("glLoadIdentity"), v8::Function::New(v8::Isolate::GetCurrent(), loadIdentity));
    object->Set(V8_String("glTranslatef"), v8::Function::New(v8::Isolate::GetCurrent(), translate));
    object->Set(V8_String("glRotatef"), v8::Function::New(v8::Isolate::GetCurrent(), rotate));
    object->Set(V8_String("glClearColor"), v8::Function::New(v8::Isolate::GetCurrent(), clearColor));
    object->Set(V8_String("glVertex3f"), v8::Function::New(v8::Isolate::GetCurrent(), vertex3f));
    object->Set(V8_String("glVertex2f"), v8::Function::New(v8::Isolate::GetCurrent(), vertex2f));
    object->Set(V8_String("glColor3f"), v8::Function::New(v8::Isolate::GetCurrent(), color3f));
    object->Set(V8_String("glClear"), v8::Function::New(v8::Isolate::GetCurrent(), clear));
    object->Set(V8_String("glBegin"), v8::Function::New(v8::Isolate::GetCurrent(), begin));
    object->Set(V8_String("glEnd"), v8::Function::New(v8::Isolate::GetCurrent(), end));
}