/**
 * @file environment.cpp
 *
 * Environment variable tools..
 */
#include "sysinc.hpp"

using namespace std;

// Local headers
#include "environment.hpp"
#include "str.hpp"

using namespace hw7;

void check_env(JSON& config)
{
    // @todo Check for all possible environment variables based on config.keys().
    const str PREFIX = PROGRAM + UNDERSCORE;
    // const auto PREFIX_LENGTH = PREFIX.length();
    
    for (char** env = environ; *env != nullptr; ++env)
    {
        const unsigned int NAME_INDEX = 0;
        const unsigned int VALUE_INDEX = 1;
        str var(*env);
        if (!var.starts_with(PREFIX)) // `var` does not belong to this program
            continue; // keep looking

        cout << "Found env var: " << var << endl;

        // auto pos = var.find(EQUAL);
        // if (pos == std::string_view::npos)
        //     continue;

        // str name  = var.substr(PREFIX_LENGTH, pos - PREFIX_LENGTH);
        // str value = var.substr(pos + 1);

        auto terms = var.split(EQUAL);
        
        cout << "name: " << terms[NAME_INDEX] << endl;
        cout << "value: " << terms[VALUE_INDEX] << endl;

        // process name/value
        const auto name = str(terms[NAME_INDEX]).lower().partition(UNDERSCORE)[1];

        cout << "JSON key: " << name << endl;
        
        if (config.contains(name)) config[name] = terms[VALUE_INDEX];

        cout << "New value: " << config[name] << endl;
    }
}