
#pragma once

#include "RasterCore.h"
#include "Modules.h"

#pragma push_macro("main")

#undef main

namespace raster {
	class RasterApp : public Poco::Util::Application {
        bool triggered;
	public:
		RasterApp();
		~RasterApp();

	protected:
		void defineOptions(Poco::Util::OptionSet& options) override;
		void initialize(Application& self) override;
		//void uninitialize() override;

		int main(const std::vector<std::string>& args) override;
    private:
        void handleVersion(const std::string& name, const std::string& v);
        void handleInfo(const std::string& name, const std::string& v);
        void handleHelp(const std::string& name, const std::string& v);

        void createOption(Poco::Util::OptionSet& options, Poco::Util::OptionCallback<RasterApp>::Callback handler, std::string arg, std::string shorthand);
	};
}

#pragma pop_macro("main")