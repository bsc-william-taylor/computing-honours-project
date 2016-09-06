#pragma once

#include "RasterCore.h"

template<typename T>
class JsObject 
{
    v8::Global<v8::Object> instance;
public:
    virtual ~JsObject() = default;

    static v8::Local<v8::Object> newTemplate(v8::Persistent<v8::ObjectTemplate>& templ)
    {
        const auto currentIsolate = v8::Isolate::GetCurrent();

        if(templ.IsEmpty())
        {
            auto objectTemplate = v8::ObjectTemplate::New(currentIsolate);
            objectTemplate->SetInternalFieldCount(1);
            templ.Reset(currentIsolate, objectTemplate);
        }

        return templ.Get(currentIsolate)->NewInstance();
    }

    static void makeConstructor(v8::Local<v8::ObjectTemplate>& cpp, v8::Local<v8::FunctionTemplate>& templ, v8::Persistent<v8::Function>& constructor, const char * name)
    {
        auto isolate = v8::Isolate::GetCurrent();
        auto context = isolate->GetCurrentContext();
        constructor.Reset(isolate, templ->GetFunction());
        cpp->Set(V8_String(name), constructor.Get(isolate));
    }

    void wrap(v8::Handle<v8::Object> handle)
    {
        handle->SetAlignedPointerInInternalField(0, this);

        instance.Reset(v8::Isolate::GetCurrent(), handle);
        instance.SetWeak(this, weakCallback, v8::WeakCallbackType::kParameter);
        instance.MarkIndependent();
    }

    template<typename T0>
    static T0 * unwrapArg(v8::Handle<v8::Object> local)
    {
        auto ptr = local->GetAlignedPointerFromInternalField(0);
        auto wrap = static_cast<JsObject<T0> *>(ptr);
        return static_cast<T0 *>(wrap);
    }

    static T * unwrap(v8::Handle<v8::Object> handle)
    {
        auto ptr = handle->GetAlignedPointerFromInternalField(0);
        auto wrap = static_cast<JsObject *>(ptr);
        return static_cast<T *>(wrap);
    }

    static T * unwrap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        auto that = args.This();
        return unwrap(that);
    }

    static void weakCallback(const v8::WeakCallbackInfo<JsObject>& data)
    {
        v8::HandleScope scope(data.GetIsolate());
        auto wrap = data.GetParameter();
        wrap->instance.Reset();
        delete wrap;
    }
};
