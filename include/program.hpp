#pragma once
/**
 * @file program.hpp
 *
 * An abstract class that runs a program.
 */

#include <iostream>   // cin & cout

#include "globals.hpp"

class Program : Globals
{
public:

    /**
     * Default constructor.
     */
    Program(int argc, char **argv) : Globals(argc, argv) {}

    /**
     * Run the program.
     */
    inline virtual unsigned int run()
    {
        dump();
        std::cout << hw7::GREETING << input << endl;
        return 0;
    }

}; // Program