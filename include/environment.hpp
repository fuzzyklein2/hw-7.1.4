#pragma once
/**
 * @file environment.hpp
 *
 * Declare environment variable functions.
 */

// C Standard Library headers
#include <cstdlib>

// 3rd Party Headers
#include "fs.hpp"
#include "str.hpp"

/**
 * @brief Check for environment variables that override `config.json`.
 *
 * Environment variables should be of the form:
 *
 *     `f"{PROGRAM}_{UNDERSCORE.join(upper(CONFIG_FILE_KEY))}`
 *
 * @param config JSON object to be modified if overridden.
 * @todo This function needs serious debugging. 🤣
 * @bug JSON object appears not to update properly?
 * @warning ⚠️ This function calls `environ`, which does not exist on Windoze.
 */
void check_env(JSON&);