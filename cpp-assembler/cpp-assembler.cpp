#include <iostream>
#include "Assembler.h"

int main()
{
	Assembler as;

    try {
	as.run("program.s");

    }
    catch (std::invalid_argument& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

}