
#pragma once

#include "RasterCore.h"
#include "Modules.h"

namespace compute
{
    class ComputeApp : public Poco::Util::Application
    {
        using OptionsCallback = Poco::Util::OptionCallback<ComputeApp>::Callback;
        using OptionSet = Poco::Util::OptionSet;

        int majorVersion, minorVersion, revVersion;

        bool skip;
    public:
        ComputeApp();
        virtual ~ComputeApp();
    protected:
        void defineOptions(Poco::Util::OptionSet& options) override;
        void initialize(Application& self) override;

        #pragma push_macro("main")
        #undef main

        int main(const std::vector<std::string>& args) override;

        #pragma pop_macro("main")
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