#pragma once
/**
 * @file config.hpp
 *
 * Configuration functions.
 */

// Local headers
#include "fs.hpp"

JSON configure(const Path&);
JSON load_data(const Path& p);
