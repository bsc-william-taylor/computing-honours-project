#pragma once

#include "RasterCore.h"
#include "JsObject.h"

class Texture : public JsObject<Texture> {
	static v8::Persistent<v8::Function> constructor;
	SDL_Texture * texture;
public:
	Texture();
	~Texture();

	static void create(v8::Local<v8::ObjectTemplate>& cpp, v8::Isolate * isolate);
	static void newInstance(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void create(const v8::FunctionCallbackInfo<v8::Value>& args);

	SDL_Texture * getTexture() const {
		return texture;
	}
};
