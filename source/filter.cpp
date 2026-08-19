/**
 * @file filter.cpp
 *
 * Member functions of `Filter` class.
 */
#include "sysinc.hpp"

using namespace std;

// Local headers
#include "filter.hpp"
#include "fs.hpp"

ErrCode Filter::process(const Path& p)
{
    cout << p << "is a " << magic_type(p) << " file." << endl;
    
    return EXIT_SUCCESS;
}