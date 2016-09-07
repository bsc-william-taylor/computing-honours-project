
#pragma once

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

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <glew.h>
#include <CL/CL.hpp>

#include <Poco/Message.h>
#include <Poco/Process.h>
#include <Poco/Util/Timer.h>
#include <Poco/PipeStream.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/Util/OptionException.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/File.h>
#include <Poco/Util/JSONConfiguration.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Notification.h>
#include <Poco/NotificationQueue.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/Net/HttpRequest.h>
#include <Poco/Net/HttpClientSession.h>
#include <Poco/Net/HttpResponse.h>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"

#include <SDL.h>
#include <SDL_image.h>
#include <functional>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opencl.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "icui18n.dll.lib")
#pragma comment(lib, "icuuc.dll.lib")
#pragma comment(lib, "v8.dll.lib")
#pragma comment(lib, "mksnapshot.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winmm.lib")

#pragma warning(disable : 4099)
#pragma warning(disable : 4244)

#define V8_Function(func) v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), func)->GetFunction()
#define V8_Integer(data) v8::Integer::New(v8::Isolate::GetCurrent(), data)
#define V8_String(data) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), data)

extern std::string cwd;
