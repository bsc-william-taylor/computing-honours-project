
#include "main.h"

using namespace raster;

int main(int argc, char* argv[]) 
{
    try
    {
        RasterApp rasterApp;
        rasterApp.init(argc, argv);
        rasterApp.run();
    }
    catch(OptionException& exception)
    {
        std::cerr << "Unknown argument -" << exception.message();
    }

    return 1;
}