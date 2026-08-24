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

// Logging module headers
#include "spdlog/spdlog.h"   // Logging module
#include "spdlog/sinks/stdout_color_sinks.h" // Screen output
#include "spdlog/sinks/basic_file_sink.h" // Log file(s)

// Local headers
#include "macros.h"

// --*-- content marker for hw7.hpp

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

using Number = unsigned int;
using ErrCode = Number;
