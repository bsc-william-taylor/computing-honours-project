#pragma once

#include "RasterCore.h"

#define EVENT_CALLBACK SDL_USEREVENT + 1
#define TIMER_CHANGE SDL_USEREVENT + 2

namespace raster {
	class JavaScriptSubsystem : public Poco::Util::Subsystem 
    {
	public:
		JavaScriptSubsystem();
		virtual ~JavaScriptSubsystem();

		void initialize(Poco::Util::Application& app) override;
		void uninitialize() override {}
		void run(std::string script);

		const char * name() const override;

		static void beginMainEventLoop(const v8::FunctionCallbackInfo<v8::Value>&);
		static void hookEventLoop(std::function<bool(SDL_Event)> callback) {
			eventHooks.push_back(callback);
		}
	private:
		static std::vector<std::function<bool(SDL_Event)>> eventHooks;
	};
}
