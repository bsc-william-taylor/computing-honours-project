
#include "ArgumentsSubsystem.h"

#define minor_version 0
#define major_version 1
#define rev_version 0

using namespace raster;

ArgumentsSubsystem::ArgumentsSubsystem()
	:triggered(false)
{
}

ArgumentsSubsystem::~ArgumentsSubsystem()
{
}

void ArgumentsSubsystem::handleHelp(const std::string& name, const std::string& v) 
{
	std::cout << "For help, contact William Taylor at B00235610@studentmail.uws.ac.uk." << std::endl;
	triggered = true;
}

void ArgumentsSubsystem::handleVersion(const std::string& name, const std::string& v)
{
	std::stringstream ss;
	ss << "Raster version: ";
	ss << major_version << ".";
	ss << minor_version << ".";
	ss << rev_version;
	std::cout << ss.str() << std::endl;
	triggered = true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void ArgumentsSubsystem::handleCreate(const std::string& name, const std::string& v)
{
	std::cout << "Creating tsconfig file..." << std::endl;

	auto basePath = SDL_GetBasePath();
	auto cwd = Poco::Path::current();
	cwd.append("tsconfig.json");

	Poco::FileInputStream input(Poco::Path(basePath, "tsconfig.json").toString());
	std::string contents;
	while(!input.eof()){
		std::string line;
		getline(input, line);
		contents += line + "\n";
	}

	input.close();

	replaceAll(contents, "#BASEPATH#", basePath);
	replaceAll(contents, "\\", "/");

	Poco::FileOutputStream stream(cwd);
	stream << contents;
	stream.close();
	
	std::cout << "File tsconfig.json created " << std::endl;
	triggered = true;
}

void ArgumentsSubsystem::handleInfo(const std::string& name, const std::string& v)
{
	std::cout << "Raster is a platform for GPU centric JavaScript applications. " << std::endl;
	triggered = true;
}

void ArgumentsSubsystem::defineOptions(Poco::Util::OptionSet& options)
{
	Poco::Util::OptionCallback<ArgumentsSubsystem> helpCallback(this, &ArgumentsSubsystem::handleHelp);
	Poco::Util::Option helpOption("help", "h", "display argument help info", false);
	helpOption.callback(helpCallback);
	helpOption.repeatable(false);

	auto versionCallback = Poco::Util::OptionCallback<ArgumentsSubsystem>(this, &ArgumentsSubsystem::handleVersion);
	auto versionOption = Poco::Util::Option("version", "v", "show version", false);

	versionOption.callback(versionCallback);
	versionOption.repeatable(false);

	auto infoCallback = Poco::Util::OptionCallback<ArgumentsSubsystem>(this, &ArgumentsSubsystem::handleInfo);
	auto infoOption = Poco::Util::Option("info", "i", "show information", false);

	infoOption.callback(infoCallback);
	infoOption.repeatable(false);

	options.addOption(versionOption);
	options.addOption(infoOption);
	options.addOption(helpOption);
}

bool ArgumentsSubsystem::wasTriggered() const
{
	return triggered;
}

void ArgumentsSubsystem::initialize(Poco::Util::Application& app)
{
}

void ArgumentsSubsystem::uninitialize()
{
}

const char * ArgumentsSubsystem::name() const
{
	return typeid(ArgumentsSubsystem).name();
}