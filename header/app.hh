#ifndef _PL_APP_HH_INCLUDED_
#define _PL_APP_HH_INCLUDED_

#include <string>

struct App {
    std::string binaryPath;

    App(int argc, const char* argv[]);
};

#endif
