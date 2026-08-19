#pragma once
/**
 * @file filter.hpp
 *
 * Class `filter` processes command line arguments as file paths.
 */

#include "types.hpp"

class Filter
{
public:

    // /**
    //  * Program constructor.
    //  * @see Program for explanation of parameters.
    //  */
    // Filter(int argc, char **argv) : Program(argc, argv) {}

    /**
     * Program constructor.
     * @see Program for explanation of parameters.
     */
    Filter(const StrList& S)
    {
        for(const auto& s : S)
        {
            paths.push_back(s);
        }
    }

    /**
     * Process the list of paths.
     * @return ErrCode.
     */
    inline ErrCode process()
    {
        for (const auto& p : paths) process(p);
        return 0;
    }

    /**
     * Process a file.
     * @return ErrCode.
     */
    virtual ErrCode process(const Path&);

protected:
    PathList paths; /// List of files to be filtered.

};
