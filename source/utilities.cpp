#include "fs.hpp"
#include "logging.hpp"
#include "utilities.hpp"

using namespace hw7;

extern "C" const char* get_program_name()
{
    return PROGRAM.c_str();
}

extern "C" void cleanup_log_files()
{
    FileSystem fs;
    // fs.dump();
    rotate_logs(fs.logs, 5);
}
