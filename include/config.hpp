#pragma once
/**
 * @file config.hpp
 *
 * Configuration functions.
 */

// Local headers
#include "fs.hpp"

// --*-- content marker for hw7.hpp

JSON configure(const Path&);
JSON load_data(const Path& p);
