
#pragma once

#include "ComputeCore.h"
#include "JsExtensions.h"

namespace compute
{
    std::string readStartupFile(std::string filename);
    std::string readFile(std::string filename);

    void registerFs(v8::Exports exports);
}
