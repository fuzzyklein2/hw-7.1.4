#pragma once
/**
 * @file types.hpp
 *
 * Define user types.
 */
#include "hw7.hpp"
using Boolean = std::atomic<bool>;
using Index = Number;
using Vector = std::vector<float>;
using ProgPtr = std::unique_ptr<Program>;
