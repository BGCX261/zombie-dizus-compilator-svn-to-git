#include <iostream>
#include <string>
#include "l09.h"

int main(int argc, char* argv[])
{
    L09
    compilador(argc,argv);

    int
    return_code;

    try
    {
        return_code = compilador.operate();
    }
    catch ( std::string err )
    {
        std::cout << err << std::endl;
        return 1;
    }

    return return_code;
}
