#pragma once

#include "RasterCore.h"
#include "JsPlatform.h"

namespace raster {
	class JsRuntime {
        static JsPlatform platform;
	public:
		JsRuntime();
		virtual ~JsRuntime();

        void printException(const v8::TryCatch& exception);
        void initialise(std::vector<std::string>& args);
		void run(std::string script);
        void run();

        static JsPlatform& GetPlatform()
        {
            return platform;
        }
    }; 		
}
