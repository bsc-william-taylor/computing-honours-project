
#include "ComputeCore.h"
#include "JsExtensions.h"

void v8::CatchExceptions(TryCatch& trycatch)
{
    if (trycatch.HasCaught())
    {
        String::Utf8Value stacktrace(trycatch.StackTrace()); 
        String::Utf8Value exception(trycatch.Exception());

        if(stacktrace.length() > 0)
        {
            std::cerr << *stacktrace << std::endl;
        }
        else
        {
            std::cerr << *exception << std::endl;
        }
    }
}

void v8::AttachFunction(Local<Object>& object, std::string name, v8::FunctionCallback callback)
{
    auto isolate = Isolate::GetCurrent();
    auto key = String::NewFromUtf8(isolate, name.c_str());

    object->Set(key, Function::New(isolate, callback));
}

void v8::AttachBoolean(Local<Object>& object, std::string name, SDL_bool value)
{
    auto isolate = Isolate::GetCurrent();
    auto key = String::NewFromUtf8(isolate, name.c_str());

    object->Set(key, Boolean::New(isolate, value ? true : false));
}

void v8::AttachNumber(Local<Object>& object, std::string name, int number)
{
    auto isolate = Isolate::GetCurrent();
    auto key = String::NewFromUtf8(isolate, name.c_str());

    object->Set(key, Number::New(isolate, number));
}

void v8::AttachString(Local<Object>& object, std::string name, std::string str)
{
    auto isolate = Isolate::GetCurrent();
    auto key = String::NewFromUtf8(isolate, name.c_str());

    object->Set(key, String::NewFromUtf8(isolate, str.c_str()));
}

void v8::Throw(std::string msg)
{
    const auto isolate = Isolate::GetCurrent();
    isolate->ThrowException(NewString(msg));
}

void v8::Run(Task* task)
{
    task->Run();
    delete task;
}

v8::Persistent<v8::ObjectTemplate> WrappedPointerTemplate;

v8::Local<v8::Object> v8::WrapPointer(void* pointer)
{
    const auto isolate = Isolate::GetCurrent();

    if (WrappedPointerTemplate.IsEmpty())
    {
        auto objectTemplate = ObjectTemplate::New(isolate);
        objectTemplate->SetInternalFieldCount(1);
        WrappedPointerTemplate.Reset(isolate, objectTemplate);
    }

    auto object = WrappedPointerTemplate.Get(isolate)->NewInstance();
    object->SetAlignedPointerInInternalField(0, pointer);
    return object;
}

v8::Local<v8::String> v8::NewString(std::string value)
{
    return String::NewFromUtf8(Isolate::GetCurrent(), value.c_str());
}

v8::Local<v8::Number> v8::NewNumber(int number)
{   
    return Number::New(Isolate::GetCurrent(), number);
}

std::string v8::GetString(Local<Value> value, std::string err)
{
    String::Utf8Value stringValue(value->ToString());
    return std::string(*stringValue);
}

int v8::GetNumber(Local<Value> value, std::string err)
{
    if(value->IsNumber())
    {
        return value.As<Number>()->Value();
    }

    Throw(err.length() ? err : "Error with number conversion");
    return 0;
}

v8::Local<v8::Function> v8::GetFunction(Local<Value> value, std::string err)
{
    return value.As<Function>();
}

v8::Local<v8::Object> v8::GetObject(Local<Value> value, std::string err)
{
    return value.As<Object>();
}