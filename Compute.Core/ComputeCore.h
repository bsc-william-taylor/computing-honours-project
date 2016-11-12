
#pragma once

#include <concurrent_vector.h>
#include <concurrent_queue.h>
#include <thread>
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
#include <Poco/Environment.h>
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
#include "include/v8-debug.h"
#include "include/v8.h"

#include <SDL.h>
#include <SDL_image.h>
#include <functional>

#include "FreeImage.h"

#pragma comment(lib, "FreeImage.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "opencl.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "icui18n.lib")
#pragma comment(lib, "icudata.lib")
#pragma comment(lib, "icustubdata.lib")
#pragma comment(lib, "icutools.lib")
#pragma comment(lib, "icuucx.lib")

#pragma comment(lib, "v8_base_0.lib")
#pragma comment(lib, "v8_base_1.lib")
#pragma comment(lib, "v8_base_2.lib")
#pragma comment(lib, "v8_base_3.lib")
#pragma comment(lib, "v8_libbase.lib")
#pragma comment(lib, "v8_libplatform.lib")
#pragma comment(lib, "v8_snapshot.lib")
#pragma comment(lib, "v8_nosnapshot.lib")

#pragma warning(disable : 4099)
#pragma warning(disable : 4244)
