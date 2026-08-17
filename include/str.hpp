#pragma once
/**
 * @file str.hpp
 *
 * A `str` class to provide some simpler functions to call on basic strings.
 * @todo Utility functions
 */

#include <string>

#include "types.hpp"

namespace hw7
{
    /**
     * Provides convenient string manipulation functions.
     *
     * Extends `std::string` with additional string manipulation functions.
     */
    class str : public String
    {
    public:

        /**
         * Default constructor.
         */
        str() = default;

        /**
         * C string constructor.
         */
        str(const char* s) : String(s) {}

        /**
         * STL basic string constructor.
         */
        str(const String& s) : String(s) {}

        /**
         * string view constructor.
         */
        str(const std::string_view& s) : String(s) {}

        /**
         * @return Lower case version of `this`.
         */
        str lower();

        /**
         * @return Upper case version of `this`.
         */
        str upper();

        /**
         * @return `StrList` of `substr`s separated by contiguous whitespace.
         */
        StrList split();

        /**
         * @param sep `str` to be used as a separator to split the `str`.
         * @return `StrList` of `substr`s separated by contiguous whitespace.
         */
        StrList split(const str&);

        /**
         * Join a list of strings using `this`.
         * @param sep `str` to be used as a separator to split the `str`.
         * @return `StrList` of `substr`s separated by contiguous whitespace.
         */            
        str join(const StrList&);

        /**
         * Replace a substring of `this` with a different string.
         * @param target The substring to find and replace.
         * @param replacement String to replace the target with.
         * @return Copy of `this` with all occurences of `target` replaced by `replacement`.
         */
        str replace(const str& pattern, const str& replacement);

        /**
         * Partition the string just like Python does.
         * @param sep `str` to be used as a separator to split the `str`.
         * @return `StrList` of 2 `substr`s but not the separator.
         */
        StrList partition(const str& pattern);


    }; //str
} // hw7