
#pragma once

#include "RasterCore.h"
#include "JsObject.h"

#include "ImageFile.h"
#include "TextFile.h"

namespace raster {
    std::string readFile(const char * filename);

	void setupFsModule(v8::Isolate * isolate, v8::Local<v8::Object>& object);
}