
#include "RasterCore.h"
#include "Application.h"

#pragma comment(lib, "Winmm.lib")

#pragma warning(disable : 4099)
#pragma warning(disable : 4244)

using namespace v8;

int main(int argc, char* argv[]) 
{
	raster::RasterApp application;
	application.init(argc, argv);
	return application.run();
}