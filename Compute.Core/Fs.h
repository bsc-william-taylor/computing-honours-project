
#pragma once

#include "RasterCore.h"

namespace compute
{
    std::string readFile(std::string filename);

    void registerFs(v8::Local<v8::Object>& object);
}