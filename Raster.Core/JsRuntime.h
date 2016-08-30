#pragma once

#include "RasterCore.h"
#include "JsPlatform.h"

namespace raster {
	class JsRuntime 
    {
        static JsPlatform platform;
	public:
		explicit JsRuntime(std::vector<std::string>& args);
		virtual ~JsRuntime();

        void printException(const v8::TryCatch& exception);
        void initialise(std::vector<std::string>& args);
		void start(std::string script);
        void start();

        static JsPlatform& GetPlatform()
        {
            return platform;
        }
    }; 		
}
