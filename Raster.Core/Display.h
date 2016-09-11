#pragma once

#include "Window.h"

namespace raster 
{
    namespace display 
    {
	    void showMessageBox(const v8::FunctionCallbackInfo<v8::Value>& args);
	    void createWindow(const v8::FunctionCallbackInfo<v8::Value>& args);
    }

	void registerDisplay(v8::Local<v8::Object>& object);
}