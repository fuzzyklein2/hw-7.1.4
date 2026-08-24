#pragma once
/**
 * @file filter.hpp
 *
 * Class `filter` processes command line arguments as file paths.
 */

// System headers
#include <vector>

#include "fs.hpp"

// --*-- content marker for hw7.hpp

template <typename T>
class Filter
{
public:

    /**
     * Default constructor.
     */
    Filter() = default;

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

template <>
ErrCode Filter<Path>::process(const Path& p)
{
    cout << p << "is a " << magic_type(p) << " file." << endl;
    
    return EXIT_SUCCESS;
}

template <>
ErrCode Filter<String>::process(const String& p)
{
    cout << p << endl;
    
    return EXIT_SUCCESS;
}


