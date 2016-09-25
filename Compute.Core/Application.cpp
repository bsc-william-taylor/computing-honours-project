
#include "Application.h"
#include "JsRuntime.h"
#include "glew.h"
#include "gl/GLU.h"
#include "gl/gl.h"

using namespace Poco::Util;
using namespace compute;

const int RevisionVersion = 1;
const int MajorVersion = 0;
const int MinorVersion = 0;

ComputeApp::ComputeApp() :
    majorVersion(MajorVersion),
    minorVersion(MinorVersion),
    revVersion(RevisionVersion),
    skip(false)
{
    setupExternalLirbaries();
    setUnixOptions(true);
}

ComputeApp::~ComputeApp()
{
    releaseExternalLirbaries();
}

void ComputeApp::initialize(Application& self)
{
    Application::initialize(self);

    Poco::Path appPath = commandPath();
    appPath.setExtension("");
    appPath.setFileName("");
    cwd = appPath.toString();

    loadConfiguration();
}

void ComputeApp::defineOptions(OptionSet& options)
{
    Application::defineOptions(options);

    createOption(options, &ComputeApp::handleVersion, "version", "v");
    createOption(options, &ComputeApp::handleHelp, "help", "h");
    createOption(options, &ComputeApp::handleInfo, "info", "i");
}

void ComputeApp::createOption(OptionSet& options, OptionsCallback handler, std::string arg, std::string shorthand)
{
    OptionCallback<ComputeApp> optionCallback(this, handler);
    Option option(arg, shorthand, "", false);
    option.callback(optionCallback);
    option.repeatable(false);
    options.addOption(option);
}

Poco::File ComputeApp::extractFilename(const std::vector<std::string>& args)
{
    Poco::Path filename(args.front());
    filename.setExtension("js");
    return Poco::File(filename);
}

#pragma push_macro("main")
#undef main

int ComputeApp::main(const std::vector<std::string>& args)
{
    if (skip)
    {
        return EXIT_OK;
    }

    Poco::Path applicationFile(commandPath());
    applicationFile.setFileName("compute");
    applicationFile.setExtension("exe");

    auto mutableArgs = const_cast<std::vector<std::string>&>(args);
    mutableArgs.insert(mutableArgs.begin(), applicationFile.toString());

    auto runtime = JsRuntime(mutableArgs);

    if (args.empty())
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

#pragma pop_macro("main")

void ComputeApp::handleHelp(const std::string& name, const std::string& v)
{
    std::cout << "For help, contact William Taylor at B00235610@studentmail.uws.ac.uk.";
    skip = true;
}

void ComputeApp::handleVersion(const std::string& name, const std::string& v)
{
    // Compute Version
    std::stringstream ss;
    ss << "v";
    ss << majorVersion << ".";
    ss << minorVersion << ".";
    ss << revVersion << std::endl << std::endl;

    // V8 version
    ss << "V8 version: " << v8::V8::GetVersion() << std::endl;

    // SDL Version
    SDL_version version;
    SDL_GetVersion(&version);
    ss << "SDL version: ";
    ss << int(version.major) << ".";
    ss << int(version.minor) << ".";
    ss << int(version.patch) << std::endl;

    // OpenGL/OpenCL Version
    ss << "OpenGL Version: " << getOpenGLVersion() << std::endl;
    ss << "OpenCL Version: " << getOpenCLVersion() << std::endl;

    std::cout << ss.str();
    skip = true;
}

void ComputeApp::handleInfo(const std::string& name, const std::string& v)
{
    std::cout << "Compute is a platform for GPU centric JavaScript applications. ";
    skip = true;
}

void ComputeApp::releaseExternalLirbaries()
{
    IMG_Quit();
    SDL_Quit();
}

void ComputeApp::setupExternalLirbaries()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
}

std::string ComputeApp::getOpenGLVersion()
{
    const auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;
    const auto window = SDL_CreateWindow("", 0, 0, 100, 100, flags);
    const auto context = SDL_GL_CreateContext(window);

    GLint major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    std::stringstream ss;
    ss << major << "." << minor;
    return ss.str();
}

std::string ComputeApp::getOpenCLVersion()
{
    auto numericChars = [](char c) { return isalpha(c) || c == ' '; };
    auto allPlatforms = std::vector<cl::Platform>();
    auto version{ 0.0 };

    cl::Platform::get(&allPlatforms);
    for (auto& platform : allPlatforms)
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