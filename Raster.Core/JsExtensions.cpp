
#include "RasterCore.h"
#include "JsExtensions.h"

void v8::CatchExceptions(TryCatch& trycatch)
{
    if (trycatch.HasCaught())
    {
        v8::String::Utf8Value exception_str(trycatch.Exception());
        const char * error = *exception_str;
        std::cerr << error << std::endl;
    }
}
