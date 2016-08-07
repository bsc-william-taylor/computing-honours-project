
#pragma once

#include "RasterCore.h"
#include "Modules.h"

#pragma push_macro("main")

#undef main

namespace raster {
	struct RasterAppOptions {
		std::string modulesDirectory;
		std::string mainScript;
	};

	class RasterApp : public Poco::Util::Application {
		Poco::AutoPtr<Poco::SimpleFileChannel> loggerChannel;
		Poco::NotificationQueue notificationQueue;
		RasterAppOptions options;
		bool nativeMode;
	public:
		RasterApp();
		~RasterApp();

		void enableNativeMode(RasterAppOptions options);
	protected:
		void defineOptions(Poco::Util::OptionSet& options) override;
		void initialize(Application& self) override;
		void uninitialize() override;

		int main(const std::vector<std::string>& args) override;
	public:
		static Poco::Path appPath;
	};
}

#pragma pop_macro("main")