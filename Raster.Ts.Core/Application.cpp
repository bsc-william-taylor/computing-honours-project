
#include "Application.h"

using namespace Poco::Util;
using namespace raster;

#pragma push_macro("main")

#undef main

RasterApp::RasterApp() :
    triggered(false)
{
}

RasterApp::~RasterApp() 
{
}

void RasterApp::initialize(Application& self)
{
    Poco::Path currentDirectory = commandPath();
    currentDirectory.setExtension("");
    currentDirectory.setFileName("");
    cwd = currentDirectory.toString();

	loadConfiguration();

	Application::initialize(self);
}

void RasterApp::defineOptions(Poco::Util::OptionSet& options)
{
    createOption(options, &RasterApp::handleVersion, "version", "v");
    createOption(options, &RasterApp::handleHelp, "help", "h");
    createOption(options, &RasterApp::handleInfo, "info", "i");

	Application::defineOptions(options);
}

void RasterApp::createOption(OptionSet& options, OptionCallback<RasterApp>::Callback handler, std::string arg, std::string shorthand)
{
    OptionCallback<RasterApp> optionCallback(this, handler);
    Option option(arg, shorthand, "", false);
    option.callback(optionCallback);
    option.repeatable(false);
    options.addOption(option);
}

int RasterApp::main(const std::vector<std::string>& args)
{
    if (triggered)
    {
        return EXIT_OK;
    }

    Poco::Path filename(args.front());
    filename.setExtension("js");

    if(filename.isFile())
    {
        std::cerr << "Starting process with file " << filename.toString() << std::endl;
    }
    else
    {
        std::cerr << "Error couldnt find file " << filename.toString() << std::endl;
    }       

    return EXIT_OK;
}

void RasterApp::handleHelp(const std::string& name, const std::string& v)
{
    std::cout << std::endl;
    std::cout << "For help, contact William Taylor at B00235610@studentmail.uws.ac.uk.";
    std::cout << std::endl;
    triggered = true;
}

void RasterApp::handleVersion(const std::string& name, const std::string& v)
{
    std::stringstream ss;
    ss << "Raster version: ";
    ss << 1 << ".";
    ss << 0 << ".";
    ss << 0;
    std::cout << std::endl << ss.str() << std::endl;
    triggered = true;
}

void RasterApp::handleInfo(const std::string& name, const std::string& v)
{
    std::cout << std::endl;
    std::cout << "Raster is a platform for GPU centric JavaScript applications. ";
    std::cout << std::endl;
    triggered = true;
}

#pragma pop_macro("main")