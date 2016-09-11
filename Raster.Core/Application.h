
#pragma once

#include "RasterCore.h"
#include "Modules.h"

#pragma push_macro("main")

#undef main
namespace raster 
{
    
	class RasterApp : public Poco::Util::Application 
    {
        using OptionsCallback = Poco::Util::OptionCallback<RasterApp>::Callback;
        using OptionSet = Poco::Util::OptionSet;

        int majorVersion, minorVersion, revVersion;

        bool skip;
	public:
		RasterApp();
		virtual ~RasterApp();
	protected:
		void defineOptions(Poco::Util::OptionSet& options) override;
		void initialize(Application& self) override;

		int main(const std::vector<std::string>& args) override;
    private:
        Poco::File extractFilename(const std::vector<std::string>& args);

        void createOption(OptionSet& options, OptionsCallback handler, std::string arg, std::string sh);
        void handleVersion(const std::string& name, const std::string& v);
        void handleInfo(const std::string& name, const std::string& v);
        void handleHelp(const std::string& name, const std::string& v);

        std::string getOpenGLVersion();
        std::string getOpenCLVersion();

        void releaseExternalLirbaries();
        void setupExternalLirbaries();
    };
}

#pragma pop_macro("main")