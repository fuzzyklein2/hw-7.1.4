/**
 * @file datetime.cpp
 *
 * Time functions.
 */

#include "sysinc.hpp"

using namespace std;

// Local headers
#include "datetime.hpp"

/**
 * now_string
 * 
 * @brief Get the current timestamp and return it.
 * 
 * @return Current timestamp as a string.
 */
String now_string()
{
    auto now = chrono::system_clock::now();
    auto t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

