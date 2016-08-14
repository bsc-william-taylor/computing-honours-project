
#include "ImageFile.h"

v8::Persistent<v8::Function> Image::constructor;

Image::Image()
	: surface(nullptr)
{
}

Image::~Image()
{
	if(surface != nullptr)
	{
		SDL_FreeSurface(surface);
	}
}

void Image::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	auto templateObject = newTemplate(newInstance, "Image");
	templateObject->PrototypeTemplate()->Set(V8_String("read"), v8::FunctionTemplate::New(isolate, read)->GetFunction());
	templateObject->InstanceTemplate()->SetAccessor(V8_String("height"), getHeight, setHeight);
	templateObject->InstanceTemplate()->SetAccessor(V8_String("width"), getWidth, setWidth);

	templateObject->InstanceTemplate()->SetAccessor(V8_String("filename"), getFilename, setFilename);
	templateObject->InstanceTemplate()->SetAccessor(V8_String("path"), getPath, setPath);
	templateObject->InstanceTemplate()->SetAccessor(V8_String("ext"), getExt, setExt);

	makeConstructor(cpp, templateObject, constructor, "Image");
}

void Image::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto that = unwrap(args);
	v8::String::Utf8Value path(args[0]);

	auto filePath = Poco::Path(Poco::Path::current());
	filePath.append(*path);

	that->surface = IMG_Load(filePath.toString().c_str());
}

void Image::setWidth(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	
}

void Image::getWidth(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	if(obj->surface == nullptr)
		info.GetReturnValue().Set(V8_Integer(-1));
	info.GetReturnValue().Set(V8_Integer(obj->surface->w));
}

void Image::setHeight(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	
}

void Image::getHeight(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	if (obj->surface == nullptr)
		info.GetReturnValue().Set(V8_Integer(-1));
	info.GetReturnValue().Set(V8_Integer(obj->surface->h));
	
}

void Image::setExt(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->ext = *v8::String::Utf8Value(value);
}

void Image::getExt(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->ext.c_str()));
}

void Image::setFilename(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->filename = *v8::String::Utf8Value(value);
}

void Image::getFilename(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->filename.c_str()));
}

void Image::setPath(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	obj->path = *v8::String::Utf8Value(value);
}

void Image::getPath(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	auto that = info.This();
	auto obj = unwrap(that);
	info.GetReturnValue().Set(V8_String(obj->path.c_str()));
}

void Image::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	auto obj = new Image();
	auto that = info.This();
	obj->wrap(that);
	info.GetReturnValue().Set(that);
}