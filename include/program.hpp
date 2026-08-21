#pragma once
/**
 * @file program.hpp
 *
 * An abstract class that runs a program.
 */

#include <iostream>   // cin & cout

#include "filter.hpp"
#include "globals.hpp"

class Program : Globals
{
public:

    /**
     * Constructor.
     * @param argc Number of CLI arguments.
     * @param argv C array of arguments as C strings.
     *
     * Arguments are just passed on to `CLI11`.
     *
     * @return Error code to (possibly) be returned by `main`
     */
    Program(int argc, char **argv) : Globals(argc, argv) {}

    /**
     * Run the program.
     */
    inline virtual ErrCode run()
    {
        dump();
        std::cout << hw7::GREETING << input << endl;

        Filter f(args);
        f.process();
        
        return 0;
    }

}; // Program