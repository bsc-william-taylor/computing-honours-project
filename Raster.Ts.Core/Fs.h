
#pragma once

#include "RasterCore.h"
#include "V8_Object.h"

#include "ImageFile.h"
#include "TextFile.h"

namespace raster {
	static void setupFsModule(v8::Isolate * isolate, v8::Local<v8::ObjectTemplate>& object) {
		TextFile::create(object, isolate);
		Image::create(object, isolate);
	}
}