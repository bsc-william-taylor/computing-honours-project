
#include "Application.h"
#include "JsRuntime.h"

using namespace Poco::Util;
using namespace raster;

#pragma push_macro("main")

#undef main

const int RasterMajorVersion = 0;
const int RasterMinorVersion = 0;
const int RasterRevVersion = 1;

RasterApp::RasterApp() :
    majorVersion(RasterMajorVersion),
    minorVersion(RasterMinorVersion),
    revVersion(RasterRevVersion),
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

void RasterApp::defineOptions(OptionSet& options)
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
    if (triggered) {
        return EXIT_OK;
    }

    JsRuntime jsRuntime;
    jsRuntime.initialise(const_cast<std::vector<std::string>&>(args));

    if(!args.empty())
    {
        Poco::Path filename(args.front());
        filename.setExtension("js");

        if (Poco::File(filename).exists())
        {
            jsRuntime.run(filename.toString());
        }
        else
        {
            std::cerr << "Error couldnt find file " << filename.toString() << std::endl;
        }
    }
    else
    {
        jsRuntime.run();
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

    // Raster Version
    ss << "Raster version: ";
    ss << majorVersion << ".";
    ss << minorVersion << ".";
    ss << revVersion << std::endl;

    // V8 version
    ss << "V8 version: ";
    ss << v8::V8::GetVersion() << std::endl;
   
    // SDL Version
    SDL_version version;
    SDL_GetVersion(&version);
    ss << "SDL version: ";
    ss << static_cast<int>(version.major) << ".";
    ss << static_cast<int>(version.minor) << ".";
    ss << static_cast<int>(version.patch);

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