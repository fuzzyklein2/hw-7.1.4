#pragma once
/**
 * @file types.hpp
 *
 * Declare namespace & type macros.
 */

#include <filesystem>
#include <map>
#include <string>
#include <vector>

// Third party headers
#include <nlohmann/json.hpp> // JSON -> struct conversion

// Local headers
#include "macros.h"

// Standard types
namespace fs = std::filesystem;
using Path = fs::path;
using String = std::string;
using StrList = std::vector<String>;
using StrDict = std::map<String, String>;
using PathList = std::vector<Path>;

// Package types
using JSON = nlohmann::json;
using Logger = std::shared_ptr<spdlog::logger>;
using LogLevel = spdlog::level::level_enum;
