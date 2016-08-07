
#include "RasterCore.h"
#include "Application.h"

#pragma comment(lib, "Winmm.lib")

using namespace v8;

int main(int argc, char* argv[]) 
{
	raster::RasterApp application;
	application.init(argc, argv);
	return application.run();
}