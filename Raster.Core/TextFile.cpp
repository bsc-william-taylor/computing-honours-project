
#include "TextFile.h"
#include "JsExtensions.h"

v8::Persistent<v8::ObjectTemplate> TextFile::objectTemplate;
v8::Persistent<v8::Function> TextFile::constructor;

TextFile::TextFile()
{
}

TextFile::~TextFile()
{
}

void TextFile::create(v8::Local<v8::Object>& raster, v8::Isolate * isolate)
{
    if (constructor.IsEmpty())
    {
        constructor.Reset(isolate, v8::Function::New(isolate, newInstance));
    }

    raster->Set(v8::String::NewFromUtf8(isolate, "TextFile"), constructor.Get(isolate));
}

void TextFile::setExt(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    obj->ext = *v8::String::Utf8Value(value);
}

void TextFile::getExt(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    info.GetReturnValue().Set(v8::NewString(obj->ext.c_str()));
}

void TextFile::setContents(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    obj->contents = *v8::String::Utf8Value(value);
}

void TextFile::getContents(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    info.GetReturnValue().Set(v8::NewString(obj->contents.c_str()));
}

void TextFile::setFilename(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    obj->filename = *v8::String::Utf8Value(value);
}

void TextFile::getFilename(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    info.GetReturnValue().Set(v8::NewString(obj->filename.c_str()));
}

void TextFile::setPath(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    obj->path = *v8::String::Utf8Value(value);
}

void TextFile::getPath(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    auto that = info.This();
    auto obj = unwrap(that);
    info.GetReturnValue().Set(v8::NewString(obj->path.c_str()));
}

void TextFile::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto that = unwrap(args);
    v8::String::Utf8Value path(args[0]);

    auto filePath = Poco::Path(Poco::Path::current());
    filePath.append(*path);
    std::ifstream file(filePath.toString());
    std::string data;

    if (file.is_open()) {
        std::string temp;
        while (getline(file, temp)) {
            data += temp + "\n";
        }

        file.close();
    }

    that->filename = filePath.getBaseName();
    that->path = filePath.absolute().toString();
    that->ext = filePath.getExtension();
    that->contents = data;
}

void TextFile::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto object = newTemplate(objectTemplate);
    auto file = new TextFile();

    object->Set(v8::NewString("read"), v8::Function::New(isolate, read));
    object->SetAccessor(v8::NewString("contents"), getContents, setContents);
    object->SetAccessor(v8::NewString("filename"), getFilename, setFilename);
    object->SetAccessor(v8::NewString("path"), getPath, setPath);
    object->SetAccessor(v8::NewString("ext"), getExt, setExt);

    file->wrap(object);

    info.GetReturnValue().Set(object);
}