/**
 * @file config.cpp
 *
 * Logging functions.
 */
#include "sysinc.hpp"

using namespace std;

// Local headers
#include "config.hpp"
#include "environment.hpp"
#include "fs.hpp"
#include "globals.hpp"
#include "types.hpp"

JSON configure(const Path& p)
{
    ostringstream ss; // for sending log output

    try
    {
        ifstream cfg(p);
        JSON config;
        cfg >> config;
    
        if (config["debug"]) cout << config["logfile"] << endl;
        else _debug = false;

        check_env(config);
        cout << "Configured logfile: " << config["logfile"] << endl;
        return config;
    }
    catch(const exception& e)
    {
        cerr << "Error loading " << p << endl;
        exit(EXIT_FAILURE);

        return false;
    }

    
}

JSON load_data(const Path& p)
{
    try
    {
        ifstream f(p);
        JSON data;
        f >> data;
        return data;
    }
    catch(const exception& e)
    {
        cerr << "Error loading " << p << endl;
        exit(EXIT_FAILURE);

        return false;
    }
}