
#pragma once

#include <Windows.h>
#include <Shlwapi.h>  
#include <future>
#include <mutex>
#include <stdio.h>
#include <memory>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <atomic>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <string>
#include <locale>
#include <map> 

#define SDL_IMG_EVERYTHING IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#undef V8_USE_EXTERNAL_STARTUP_DATA

#include <CL/CL.hpp>

#include <Poco/Message.h>
#include <Poco/Process.h>
#include <Poco/Util/Timer.h>
#include <Poco/PipeStream.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/File.h>
#include <Poco/Util/JSONConfiguration.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Notification.h>
#include <Poco/NotificationQueue.h>
#include <Poco/SimpleFileChannel.h>

#include "include/libplatform/libplatform.h"
#include "include/v8-debug.h"
#include "include/v8.h"

#include <SDL.h>
#include <SDL_image.h>
#include <functional>

#pragma comment(lib, "opencl.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "icui18n.lib")
#pragma comment(lib, "icuuc.lib")
#pragma comment(lib, "v8_base_0.lib")
#pragma comment(lib, "v8_base_1.lib")
#pragma comment(lib, "v8_base_2.lib")
#pragma comment(lib, "v8_base_3.lib")
#pragma comment(lib, "v8_libbase.lib")
#pragma comment(lib, "v8_libplatform.lib")
#pragma comment(lib, "v8_nosnapshot.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma warning(disable : 4099)
#pragma warning(disable : 4244)


#define V8_Function(func) v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), func)->GetFunction()
#define V8_Integer(data) v8::Integer::New(v8::Isolate::GetCurrent(), data)
#define V8_String(data) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), data)

extern std::string cwd;
