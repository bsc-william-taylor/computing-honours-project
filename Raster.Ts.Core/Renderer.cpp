#include "Renderer.h"
#include "Window.h"
#include "Texture.h"

using namespace raster;

v8::Persistent<v8::Function> Renderer::constructor;

Renderer::Renderer()
	: renderer(nullptr)
{
	
}

Renderer::~Renderer()
{
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}
	
}

void Renderer::create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate)
{
	auto templateObject = newTemplate(newInstance, "Renderer");

	templateObject->PrototypeTemplate()->Set(V8_String("initialise"), v8::FunctionTemplate::New(isolate, initialise)->GetFunction());
	templateObject->PrototypeTemplate()->Set(V8_String("drawTexture"), v8::FunctionTemplate::New(isolate, drawTexture)->GetFunction());
	templateObject->PrototypeTemplate()->Set(V8_String("present"), v8::FunctionTemplate::New(isolate, present)->GetFunction());
	templateObject->PrototypeTemplate()->Set(V8_String("clear"), v8::FunctionTemplate::New(isolate, clear)->GetFunction());

	makeConstructor(cpp, templateObject, constructor, "Renderer");
}

void Renderer::newInstance(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	auto obj = new Renderer();
	auto that = info.This();
	obj->wrap(that);
	info.GetReturnValue().Set(that);
}

void Renderer::initialise(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto local(v8::Local<v8::Object>::Cast(args[0]));
	auto window = unwrapArg<Window>(local);
	auto that = unwrap(args);

	that->renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
		
	if (that->renderer == nullptr)
	{
		std::cerr << "Error with creating renderer :" << SDL_GetError() << std::endl;
	}
}

void Renderer::present(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto that = unwrap(args);

	if(that->renderer != nullptr) {
		SDL_RenderPresent(that->renderer);
	}
}

void Renderer::drawTexture(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto that = unwrap(args);

	if(args.Length() == 2)
	{
		auto texture = unwrapArg<Texture>(v8::Local<v8::Object>::Cast(args[0]));
		auto rect = v8::Handle<v8::Object>::Cast(args[1]);
		
		auto x = rect->Get(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "x"));
		auto y = rect->Get(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "y"));
		auto w = rect->Get(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "w"));
		auto h = rect->Get(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "h"));
		
		SDL_Rect position = {
			x->ToInteger()->Value(), 
			y->ToInteger()->Value(), 
			w->ToInteger()->Value(), 
			h->ToInteger()->Value()
		};

		auto surface = texture->getTexture();

		if(surface != nullptr)
		{
			if (that->renderer != nullptr) {
				if(SDL_RenderCopy(that->renderer, surface, nullptr, &position) == -1)
				{
					std::cout << "SDL_RenderCopy: " << SDL_GetError() << std::endl;
				}
			}
		}
	}
}

void Renderer::clear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto that = unwrap(args);
	auto r = 0, g = 0, b = 0, a = 0;

	if (args.Length() == 4) {
		r = args[0]->ToInteger()->Value();
		g = args[1]->ToInteger()->Value();
		b = args[2]->ToInteger()->Value();
		a = args[3]->ToInteger()->Value();
	}

	if (that->renderer != nullptr) {
		SDL_SetRenderDrawColor(that->renderer, r, g, b, a);
		SDL_RenderClear(that->renderer);
	}
}
