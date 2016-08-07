#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Texture.h"

namespace raster {
	class Renderer : public JsObject<Renderer> {
		static v8::Persistent<v8::Function> constructor;
		SDL_Renderer * renderer;
		std::mutex mutex;
	public:
		Renderer();
		~Renderer();

		SDL_Renderer * getRenderer() const {
			return renderer;
		}

		static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);
		static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
		static void initialise(const v8::FunctionCallbackInfo<v8::Value>& args);
		static void present(const v8::FunctionCallbackInfo<v8::Value>& args);
		static void clear(const v8::FunctionCallbackInfo<v8::Value>& args);
		static void drawTexture(const v8::FunctionCallbackInfo<v8::Value>& args);
	};

	static void setupGraphicsModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		Renderer::create(object, isolate);
		Texture::create(object, isolate);
	}
}
