
#pragma once

#include "ComputeCore.h"
#include "JsExtensions.h"

namespace compute
{
    std::string readFile(std::string filename);

    void registerFs(v8::Exports exports);
}
