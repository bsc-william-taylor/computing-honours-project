
#include "RasterCore.h"
#include "JsExtensions.h"

void v8::CatchExceptions(TryCatch& trycatch)
{
    if (trycatch.HasCaught())
    {
        String::Utf8Value stacktrace(trycatch.StackTrace()); 
        std::cerr << *stacktrace << std::endl;
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

void v8::Throw(const FunctionCallbackInfo<Value>& args, std::string msg)
{
    const auto isolate = args.GetIsolate();
    const auto error = String::NewFromUtf8(isolate, msg.c_str());

    if (isolate && msg.length() >= 0)
    {
        isolate->ThrowException(error);
    }
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
    return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), value.c_str());
}