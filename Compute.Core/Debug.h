
#pragma once

#include "ComputeCore.h"
#include "JsExtensions.h"

extern v8::Persistent<v8::Context> _context;

namespace compute
{
    void registerDebug(v8::Exports exports);
}

