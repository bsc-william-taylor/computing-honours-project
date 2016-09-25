
#include "main.h"

using namespace compute;

int main(int argc, char* argv[])
{
    try
    {
        ComputeApp rasterApp;
        rasterApp.init(argc, argv);
        rasterApp.run();
    }
    catch (OptionException& exception)
    {
        std::cerr << "Unknown argument -" << exception.message();
    }

    return 1;
}