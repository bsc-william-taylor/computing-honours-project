
#pragma once

#include "RasterCore.h"
#include "JsObject.h"
#include "Platform.h"
#include "Device.h"
#include "Context.h"
#include "Program.h"
#include "Buffer.h"
#include "Kernel.h"
#include "CommandQueue.h"

namespace raster {
    void getPlatforms(const v8::FunctionCallbackInfo<v8::Value>& args);

    void registerOpenCL(v8::Local<v8::Object>& object);
}
