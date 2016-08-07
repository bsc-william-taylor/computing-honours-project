#pragma once

#include "RasterCore.h"

namespace raster {
	class ArgumentsSubsystem : public Poco::Util::Subsystem
	{
		bool triggered;
	public:
		ArgumentsSubsystem();
		~ArgumentsSubsystem();

		bool wasTriggered() const;

		void defineOptions(Poco::Util::OptionSet& options) override;
		void initialize(Poco::Util::Application& app) override;
		void uninitialize() override;

		const char * name() const override;
	private:
		void handleVersion(const std::string& name, const std::string& v);
		void handleCreate(const std::string& name, const std::string& v);
		void handleInfo(const std::string& name, const std::string& v);
		void handleHelp(const std::string& name, const std::string& v);
	};
}