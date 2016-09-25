
#include "OpenGL.h"
#include "gl/GLU.h"
#include "gl/gl.h"
#include "JsExtensions.h"

void compute::glClearColor(const v8::FunctionCallbackInfo<v8::Value>& args)
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

void compute::glClear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glClear(args[0]->NumberValue());
    }
}

void compute::glBegin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glBegin(static_cast<GLenum>(args[0]->NumberValue()));
    }
}

void compute::glColor3(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();

        glColor3f(r, g, b);
    }
}

void compute::glVertex2(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 2)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();

        glVertex2f(x, y);
    }
}

void compute::glVertex3(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glVertex3f(x, y, z);
    }
}

void compute::glLoadIdentity(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ::glLoadIdentity();
}

void compute::glMatrixMode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glMatrixMode(args[0].As<v8::Number>()->Value());
    }
}

void compute::glTranslate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glTranslatef(x, y, z);
    }
}

void compute::glRotate(const v8::FunctionCallbackInfo<v8::Value>& args)
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

void compute::glPerspective(const v8::FunctionCallbackInfo<v8::Value>& args)
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

void compute::glEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ::glEnd();
}

void compute::glEnable(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() == 1)
    {
        ::glEnable(args[0].As<v8::Integer>()->Value());
    }

}

void compute::registerOpenGL(v8::Local<v8::Object>& object) 
{
    AttachFunction(object, "gluPerspective", glPerspective);
    AttachFunction(object, "glEnable", glEnable);
    AttachFunction(object, "glMatrixMode", glMatrixMode);
    AttachFunction(object, "glLoadIdentity", glLoadIdentity);
    AttachFunction(object, "glTranslatef", glTranslate);
    AttachFunction(object, "glRotatef", glRotate);
    AttachFunction(object, "glClearColor", glClearColor);
    AttachFunction(object, "glVertex3f", glVertex3);
    AttachFunction(object, "glVertex2f", glVertex2);
    AttachFunction(object, "glColor3f", glColor3);
    AttachFunction(object, "glClear", glClear);
    AttachFunction(object, "glBegin", glBegin);
    AttachFunction(object, "glEnd", glEnd);
}