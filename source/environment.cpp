/**
 * @file environment.cpp
 *
 * Environment variable tools..
 */
#include "sysinc.hpp"

using namespace std;

// Local headers
#include "environment.hpp"
#include "types.hpp"

void check_env(JSON& config)
{
    // @todo Check for all possible environment variables based on config.keys().
    const char* s = getenv("hello_LOGFILE");
    // cout << s << endl;
    if (s)
    {
        cout << "Environment variable hello_LOGFILE is set.";
        cout << "`hello_LOGFILE` = " << s << endl;
        config["logfile"] = s;
    }
    else
    {
        // cout << "ENVIRONMENT: hello_LOGFILE NOT FOUND!" << endl;
    }
}