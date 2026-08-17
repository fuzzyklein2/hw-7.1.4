/**
 * @file environment.cpp
 *
 * Environment variable tools..
 */
#include "sysinc.hpp"

using namespace std;

// Local headers
#include "environment.hpp"

void check_env(JSON& config)
{
    // @todo Check for all possible environment variables based on config.keys().
    const str PREFIX = PROGRAM + UNDERSCORE;
    const auto PREFIX_LENGTH = PREFIX.length();
    
    for (char** env = environ; *env != nullptr; ++env)
    {
        std::string_view var(*env);
        if (!var.starts_with(PREFIX)) // `var` does not belong to this program
            continue; // keep looking

        auto pos = var.find(EQUAL);
        if (pos == std::string_view::npos)
            continue;

        str name  = var.substr(PREFIX_LENGTH, pos - PREFIX_LENGTH);
        str value = var.substr(pos + 1);

        // process name/value
        name = name.lower().replace(UNDERSCORE, SPACE);
        if (config.contains(name)) config[name] = value;
    }
}