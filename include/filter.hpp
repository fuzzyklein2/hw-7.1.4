#pragma once
/**
 * @file filter.hpp
 *
 * Class `filter` processes command line arguments as file paths.
 */

// #include <string>
#include "program.hpp"
#include "types.hpp"

class Filter : public Program
{
public:

    /**
     * Program constructor.
     * @see Program for explanation of parameters.
     */
    Filter(int argc, char **argv) : Program(argc, argv) {}

    /**
     * Run the program.
     * @return Error code.
     */
    virtual unsigned int run();

};
