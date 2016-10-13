
#include "main.h"

using namespace compute;

int main(int argc, char* argv[])
{
    try
    {
        ComputeApp compute;
        compute.init(argc, argv);
        compute.run();
    }
    catch (OptionException& exception)
    {
        std::cerr << "Unknown argument -" << exception.message();
    }

    return 0;
}