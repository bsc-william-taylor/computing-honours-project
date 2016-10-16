
#include "main.h"

using namespace compute;

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);

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