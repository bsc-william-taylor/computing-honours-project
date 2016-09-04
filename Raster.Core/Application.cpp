
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
    setupExternalLirbaries();
    setUnixOptions(true);
}

RasterApp::~RasterApp() 
{
    releaseExternalLirbaries();
}

void RasterApp::initialize(Application& self)
{
    Application::initialize(self);

    Poco::Path appPath = commandPath();
    appPath.setExtension("");
    appPath.setFileName("");
    cwd = appPath.toString();

	loadConfiguration();
}

void RasterApp::defineOptions(OptionSet& options)
{
    Application::defineOptions(options);
    
    createOption(options, &RasterApp::handleVersion, "version", "v");
    createOption(options, &RasterApp::handleHelp, "help", "h");
    createOption(options, &RasterApp::handleInfo, "info", "i");
}

void RasterApp::createOption(OptionSet& options, OptionCallback<RasterApp>::Callback handler, std::string arg, std::string shorthand)
{
    OptionCallback<RasterApp> optionCallback(this, handler);
    Option option(arg, shorthand, "", false);
    option.callback(optionCallback);
    option.repeatable(false);
    options.addOption(option);
}

Poco::File RasterApp::extractFilename(const std::vector<std::string>& args)
{
    Poco::Path filename(args.front());
    filename.setExtension("js");
    return Poco::File(filename);
}


int RasterApp::main(const std::vector<std::string>& args)
{
    if (triggered)
    {
        return EXIT_OK;
    }

    Poco::Path applicationFile(commandPath());
    applicationFile.setFileName("raster");
    applicationFile.setExtension("exe");

    auto mutableArgs = const_cast<std::vector<std::string>&>(args);
    mutableArgs.insert(mutableArgs.begin(), applicationFile.toString());

    auto runtime = JsRuntime(mutableArgs);

    if(args.empty())
    {
        runtime.start();
    }
    else
    {
        auto script = extractFilename(args);

        if (script.exists())
        {
            runtime.start(script.path());
        }
        else
        {
            std::cerr << "Error couldnt find file " << script.path() << std::endl;
        }
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

void RasterApp::releaseExternalLirbaries()
{
    IMG_Quit();
    SDL_Quit();
}

void RasterApp::setupExternalLirbaries()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(SDL_IMG_EVERYTHING);
}

#pragma pop_macro("main")