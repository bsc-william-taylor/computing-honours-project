
#include "Application.h"
#include "JsRuntime.h"
#include "glew.h"
#include "gl/GLU.h"
#include "gl/gl.h"

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
    skip(false)
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

void RasterApp::createOption(OptionSet& options, OptionsCallback handler, std::string arg, std::string shorthand)
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
    if (skip)
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
    std::cout << "For help, contact William Taylor at B00235610@studentmail.uws.ac.uk.";
    skip = true;
}

void RasterApp::handleVersion(const std::string& name, const std::string& v)
{
    std::stringstream ss;
    skip = true;

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
    ss << static_cast<int>(version.patch) << std::endl;

    // OpenGL/OpenCL Version
    ss << "OpenGL Version: ";
    ss << getOpenGLVersion() << std::endl;
    ss << "OpenCL Version: ";
    ss << getOpenCLVersion();

    std::cout << ss.str();
}

void RasterApp::handleInfo(const std::string& name, const std::string& v)
{
    std::cout << "Raster is a platform for GPU centric JavaScript applications. ";
    skip = true;
}

void RasterApp::releaseExternalLirbaries()
{
    IMG_Quit();
    SDL_Quit();
}

void RasterApp::setupExternalLirbaries()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
}

std::string RasterApp::getOpenGLVersion()
{
    const auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;
    const auto window = SDL_CreateWindow("", 0, 0, 100, 100, flags);
    const auto context = SDL_GL_CreateContext(window);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    std::stringstream ss;
    ss << major << "." << minor;
    return ss.str();    
}

std::string RasterApp::getOpenCLVersion()
{
    auto numericChars = [](char c) { return isalpha(c) || c == ' '; };
    auto allPlatforms = std::vector<cl::Platform>();
    auto version{ 0.0 };

    cl::Platform::get(&allPlatforms);
    for(auto& platform : allPlatforms)
    {
        auto versionString = platform.getInfo<CL_PLATFORM_VERSION>();
        auto begin = versionString.begin();
        auto end = versionString.end();

        versionString.erase(std::remove_if(begin, end, numericChars), end);

        auto pv = atoi(versionString.c_str());
        version = pv > version ? pv : version;
    }

    std::stringstream ss;
    ss << std::fixed;
    ss << std::setprecision(2);
    ss << version;
    return ss.str();
}

#pragma pop_macro("main")