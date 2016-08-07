
#include "Texture.h"
#include "ImageFile.h"
#include "Renderer.h"

v8::Persistent<v8::Function> Texture::constructor;

Texture::Texture()
	: texture(nullptr)
{
	
}

Texture::~Texture()
{
	
}

void Texture::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	auto templateObject = newTemplate(newInstance, "Texture");

	templateObject->PrototypeTemplate()->Set(V8_String("create"), v8::FunctionTemplate::New(isolate, create)->GetFunction());

	makeConstructor(cpp, templateObject, constructor, "Texture");
}

void Texture::create(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto that = unwrap(args);

	if(args.Length() == 2)
	{
		auto renderer = unwrapArg<raster::Renderer>(v8::Local<v8::Object>::Cast(args[0]));
		auto image = unwrapArg<Image>(v8::Local<v8::Object>::Cast(args[1]));

		auto rawRenderer = renderer->getRenderer();
		auto rawSurface = image->getSurface();

		if(rawRenderer != nullptr && rawSurface != nullptr)
		{
			that->texture = SDL_CreateTextureFromSurface(rawRenderer, rawSurface);
		}
	}
}

void Texture::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	auto obj = new Texture();
	auto that = info.This();
	obj->wrap(that);
	info.GetReturnValue().Set(that);
}