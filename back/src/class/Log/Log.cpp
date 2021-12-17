#include "Log.h"

using namespace std;

Log::Log()
{
}

Log::~Log()
{
}

/******************
*     Methods     *
*******************/

void Log::write(string type, string msg) {
    string logMsg = "[\033[1;32m" + type + "\033[0m] " + msg;
    printf("%s\n", logMsg.c_str());
}

void Log::writeError(string msg) {
    string logMsg = "[\033[1;31mERROR\033[0m] " + msg;
    printf("%s\n", logMsg.c_str());
}
