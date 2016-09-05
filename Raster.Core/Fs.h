
#pragma once

#include "RasterCore.h"
#include "JsObject.h"

#include "ImageFile.h"
#include "TextFile.h"

namespace raster {
    std::string readFile(const char * filename);

	void registerFs(v8::Local<v8::Object>& object);
}