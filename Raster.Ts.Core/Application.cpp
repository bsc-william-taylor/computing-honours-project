
#include "Application.h"
#include "ArgumentsSubsystem.h"
#include "JavaScriptSubSystem.h"

using namespace raster;

Poco::Path RasterApp::appPath;

#pragma push_macro("main")

#undef main

RasterApp::RasterApp() : 
    loggerChannel(Poco::AutoPtr<Poco::SimpleFileChannel>(new Poco::SimpleFileChannel)), 
    nativeMode(false)
{
	addSubsystem(new ArgumentsSubsystem());
	addSubsystem(new JavaScriptSubsystem());
}

RasterApp::~RasterApp() 
{
}

void RasterApp::initialize(Application& self)
{
	appPath = this->commandPath();
	appPath.setExtension("");
	appPath.setFileName("");

	loadConfiguration();

	Application::initialize(self);
}

void RasterApp::uninitialize()
{
	Application::uninitialize();
}

void RasterApp::defineOptions(Poco::Util::OptionSet& options)
{
	Application::defineOptions(options);
}

int RasterApp::main(const std::vector<std::string>& args)
{
    auto directory = appPath.toString();
    compilerDirectory = directory;
    modulesDirectory = directory;

    if (args.size() == 1 && !getSubsystem<ArgumentsSubsystem>().wasTriggered())
    {
        auto filename = args.front();

        if (filename.length() != 0)
        {
            getSubsystem<JavaScriptSubsystem>().run(filename);
        }
    }

    return EXIT_OK;
}

void RasterApp::enableNativeMode(RasterAppOptions options)
{
	this->options = options;
	this->nativeMode = true;
}

#pragma pop_macro("main")