#pragma once
/**
 * @file filter.hpp
 *
 * Class `filter` processes command line arguments as file paths.
 */

#include <vector>

#include "types.hpp"

template <typename T>
class Filter
{
public:

    /**
     * StrList constructor.
     * @param S A list of strings.
     */
    Filter(const StrList& S)
    {
        for(const auto& s : S)
        {
            elements.push_back(s);
        }
    }

    /**
     * Process the list of paths.
     * @return ErrCode.
     */
    inline ErrCode process()
    {
        for (const auto& p : elements) process(p);
        return 0;
    }

    /**
     * Process a file.
     * @return ErrCode.
     */
    virtual ErrCode process(const T&);

protected:
    std::vector<T> elements; /// List of files to be filtered.

};
