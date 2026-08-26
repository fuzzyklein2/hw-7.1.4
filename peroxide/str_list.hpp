#pragma once
/**
 * @file str_list.hpp
 *
 * Exists mainly for the `text` constructor.
 */
#include "hw7.hpp"

namespace h2o2
{
    class str_list : public StrList
    {
    public:

        /**
         * Default constructor.
         */
        str_list() = default;

        /**
         * Construct a `StrList` by splitting `text` on `endl`.
         * 
         * Make sure the returned value is a `str_list` and no demotion occurs.
         */
        str_list(const str& text) : StrList(text.split(str("\n"))) {}
    }; // str_list
} // h2o2
